import polib
import re
import argparse
import code_generator.code_generator as codegen
import code_generator.cpp_generator as cppgen
import os
from io import StringIO
import json
# import xmltodict
# import requests


def wrap_u8_sv8(entry: str) -> str:
    return f'u8\"{entry}\"_sv8'


def extract_string_name(parser_indicator, comment_string):
    _comment = re.search(parser_indicator + '(.+?)(?:$|\n)', comment_string)  # Get the string between the indicator and a newline or end of string
    return _comment.group(1) if _comment is not None else None  # Check that some parser comment was actually extracted


def new_extract(path: str, pot_name: str, encoding: str, map_indicator: str, array_indicator: str):
    _po_map = {pot_name: {}}
    _key_list = []
    _array_names = {}
    _map_name = ""
    try:
        pot_file = polib.pofile(f'{path}{pot_name}.pot', encoding=encoding)  # Open the po file in the directory
        _key_list = [x.msgid for x in pot_file.untranslated_entries()]
        _po_map[pot_name] = {"keys": _key_list}
        for _index in range(0, len(pot_file.untranslated_entries())):

            result = extract_string_name(map_indicator, pot_file.untranslated_entries()[_index].comment)
            if result is not None:
                _map_name = result

            array_name = extract_string_name(array_indicator, pot_file.untranslated_entries()[_index].comment)
            if array_name is None:
                array_name = f'array_{abs(hash(pot_name))}'
            _array_names[pot_file.untranslated_entries()[_index].msgid] = array_name
        _po_map[pot_name] |= {"map_name": _map_name}
        _po_map[pot_name] |= {"array_names": _array_names}
    except IOError:
        print(f"Could not open the po file with the path: {pot_name}.pot")

    try:
        for sub_dir in (sub_dir for sub_dir in os.scandir(path) if sub_dir.is_dir()):  # Go through each of the directory items that is a sub directory
            file_path_and_name = f"{path}{sub_dir.name}/{pot_name}.po"
            try:
                po_file = polib.pofile(file_path_and_name, encoding=encoding)  # Open the po file in the directory
                # Generate the dict of all the translations for the input file name
                _po_map[pot_name][sub_dir.name] = {po_file.translated_entries()[i].msgid: po_file.translated_entries()[i].msgstr for i in range(len(po_file.translated_entries()))}
            except IOError:
                print(f"Could not open the po file with the path: {file_path_and_name}")
    except FileNotFoundError:
        print(f"Could not find the folder passed to -p (--path): {args['path']}")  # If the top level directory does not exist
    return _po_map


def gen_translated_map(translated_array_names: list, map_name: str):
    str_file = StringIO()
    hpp = codegen.CodeFile('', str_file)
    comma_separated_strs = ', '.join(translated_array_names)
    main_map = cppgen.CppVariable(name=f'{map_name}', type='std::array', is_constexpr=True, initialization_value=f'{{{comma_separated_strs}}}')
    main_map.render_to_string(hpp)
    str_file.seek(0)
    return str_file.read()


def gen_translated_array(translated_strs: list, array_name: str) -> str:
    str_file = StringIO()
    hpp = codegen.CodeFile('', str_file)
    comma_separated_strs = ', '.join([wrap_u8_sv8(x) for x in translated_strs])
    main_map = cppgen.CppVariable(name=f'{array_name}', type='std::array', is_constexpr=True, initialization_value=f'{{{comma_separated_strs}}}')
    main_map.render_to_string(hpp)
    str_file.seek(0)
    return str_file.read()


def process_pot(pot_name: str, encoding: str, parser_indicator: str) -> [list, dict]:
    _key_strings = []
    _map_names = {}
    try:
        po_file = polib.pofile(pot_name, encoding=encoding)  # Open the po file in the directory
        _key_strings = [x.msgid for x in po_file.untranslated_entries()]
        for _index in range(0, len(po_file.untranslated_entries())):
            _map_names[po_file.untranslated_entries()[_index].msgid] = extract_string_name(parser_indicator, po_file.untranslated_entries()[_index].comment)
    except IOError:
        print(f"Could not open the po file with the path: {pot_name}")
    return _key_strings, _map_names


def extract_translated(path: str, file_name: str, encoding: str) -> dict:
    _translated_dict = {}
    try:
        for sub_dir in (sub_dir for sub_dir in os.scandir(path) if sub_dir.is_dir()):  # Go through each of the directory items that is a sub directory
            file_path_and_name = f"{path}{sub_dir.name}/{file_name}"
            try:
                po_file = polib.pofile(file_path_and_name, encoding=encoding)  # Open the po file in the directory
                # Generate the dict of all the translations for the input file name
                _translated_dict[sub_dir.name] = {po_file.translated_entries()[i].msgid: po_file.translated_entries()[i].msgstr for i in range(len(po_file.translated_entries()))}
            except IOError:
                print(f"Could not open the po file with the path: {file_path_and_name}")
    except FileNotFoundError:
        print(f"Could not find the folder passed to -p (--path): {args['path']}")  # If the top level directory does not exist
    return _translated_dict


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Convert PO files to header files')
    parser.add_argument('--po',
                        help='The input file name | note: This is usually the same name as the .pot file used to generate the .po files',
                        required=False)  # TODO: Make required
    parser.add_argument('--pot',
                        help='The input template file name | note: This is usually the same name as the .pot file used to generate the .po files',
                        required=False)  # TODO: Make required
    parser.add_argument('-o', '--output',
                        help='The output file name',
                        required=False)  # TODO: Make required
    parser.add_argument('-p', '--path',
                        help='The input folder path',
                        required=False)  # TODO: Make required
    parser.add_argument('-l', '--locale',
                        help='The input folder path',
                        required=False)  # TODO: Make required
    parser.add_argument('-c', '--comment',
                        help='The comment string which indicates the start of a parser specific directive',
                        default='PARSER: ', required=False)
    parser.add_argument('-e', '--encoding',
                        help='The encoding of the input and output file | eg: utf8',
                        default='utf8', required=False)
    args = vars(parser.parse_args())

    # translated_data = extract_translated(args['path'], args['po'], args['encoding'])
    # print(translated_data)

    # key_strings, array_names = process_pot(args['pot'], args['encoding'], args['comment'])
    # print(key_strings)
    # print(array_names)

    new_format = new_extract(path='locale/', pot_name='main', encoding='UTF-8', map_indicator='E18_MAP: ', array_indicator='E18_ARR: ')

    print(json.dumps(new_format, indent=4))

    # array_map = []
    # for key in key_strings:
    #     translated_list = [key] + [translated_data[locale][key] for locale in translated_data]
    #     array_name = array_names[key]
    #     array_map.append(array_name)
    #     print(gen_translated_array(translated_list, array_name))
    #     print(gen_translated_map(array_map))

    # pofile = polib.pofile('po/es_ES/main_es_ES.po', encoding=args['encoding'])
    # print(pofile.metadata['Language'])
    # print(Locales.locales[pofile.metadata['Language']])
    # print(pofile.translated_entries()[1].msgstr)

    # outfile = open('Example.hpp', 'w', encoding=args['encoding'])
    # hpp = codegen.CodeFile('Example.hpp', outfile)
    # main_map = cppgen.CppVariable(name='main_map', type='std::array', is_constexpr=True,
    #                                                     initialization_value=f'{{{strings}}}')
    # main_map.render_to_string(hpp)

    # with requests.get("https://raw.githubusercontent.com/unicode-org/cldr/release-41/common/main/en.xml") as response:
    #     xml_dict = xmltodict.parse(response.text, encoding='UTF-8')['ldml']
    #     print(xml_dict["numbers"]["symbols"]["decimal"])
    #     print(xml_dict["numbers"]["symbols"]["group"])
    #     print(xml_dict["numbers"]["symbols"])
