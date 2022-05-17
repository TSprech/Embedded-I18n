import polib
import re
import argparse
import code_generator.code_generator as codegen
import code_generator.cpp_generator as cppgen
import os
from io import StringIO
import json
import emoji
# from ordered_set import OrderedSet
# import xmltodict
# import requests


def wrap_u8_sv8(entry: str) -> str:
    return f'u8\"{entry}\"_sv8'


def extract_string_name(parser_indicator, comment_string):
    _comment = re.search(parser_indicator + '(.+?)(?:$|\n)', comment_string)  # Get the string between the indicator and a newline or end of string
    return _comment.group(1) if _comment is not None else None  # Check that some parser comment was actually extracted


# def extract_pot(path: str, pot_name: str, encoding: str, map_indicator: str, array_indicator: str) -> [list, dict, dict, dict]:
def extract_pot(path: str, pot_name: str, encoding: str, map_indicator: str, array_indicator: str) -> dict:
    _po_map = {pot_name: {}}
    _key_list = []
    _array_names = {}
    _map_name = ""
    try:
        pot_file = polib.pofile(f'{path}/{pot_name}.pot', encoding=encoding)  # Open the po file in the directory
        _key_list = [x.msgid for x in pot_file.untranslated_entries()]  # Generate the list of keys
        _po_map[pot_name] = {"keys": _key_list}  # Assign it to a dict entry
        for _index in range(0, len(pot_file.untranslated_entries())):
            # First, get the array name from the comments
            result = extract_string_name(map_indicator, pot_file.untranslated_entries()[_index].comment)
            if result is not None:  # As each comment is checked to see if the current one contains the map name
                _map_name = result

            # Next, extract the array names from each comment, or generate a unique hash name
            array_name = extract_string_name(array_indicator, pot_file.untranslated_entries()[_index].comment)
            if array_name is None:
                array_name = f'array_{abs(hash(pot_file.untranslated_entries()[_index].msgid))}'
            _array_names[pot_file.untranslated_entries()[_index].msgid] = array_name
        _po_map[pot_name] |= {"map_name": _map_name}
        _po_map[pot_name] |= {"array_names": _array_names}
    except IOError:
        print(f"Could not open the po file with the path: {pot_name}.pot")
    return _po_map


def extract_po(path: str, pot_name: str, encoding: str) -> dict:
    _po_map = {pot_name: {'data': {}}}
    try:
        for sub_dir in (sub_dir for sub_dir in os.scandir(path) if sub_dir.is_dir()):  # Go through each of the directory items that is a sub directory
            file_path_and_name = f"{path}/{sub_dir.name}/{pot_name}.po"
            try:
                po_file = polib.pofile(file_path_and_name, encoding=encoding)  # Open the po file in the directory
                # Generate the dict of all the translations for the input file name
                _po_map[pot_name]['data'][sub_dir.name] = {po_file.translated_entries()[i].msgid: po_file.translated_entries()[i].msgstr for i in range(len(po_file.translated_entries()))}
            except IOError:
                print(f"Could not open the po file with the path: {file_path_and_name}")
    except FileNotFoundError:
        print(f"Could not find the folder passed to -p (--path): {args['path']}")  # If the top level directory does not exist
    return _po_map


def new_extract(path: str, pot_name: str, encoding: str, map_indicator: str, array_indicator: str):
    _po_map = extract_pot(path, pot_name, encoding, map_indicator, array_indicator)
    _po_map[pot_name] |= extract_po(path, pot_name, encoding)[pot_name]
    return _po_map


def gen_translated_map(translated_array_names: list, map_name: str):
    str_file = StringIO()
    hpp = codegen.CodeFile('', str_file)
    comma_separated_strs = ', \n'.join(translated_array_names)
    main_map = cppgen.CppVariable(name=f'{map_name}', type='eternal::translation_map', is_constexpr=True, initialization_value=f'({{{comma_separated_strs}}})')
    main_map.render_to_string(hpp)
    str_file.seek(0)
    return str_file.read()


def gen_translated_array(translated_strs: list, array_name: str) -> str:
    str_file = StringIO()
    hpp = codegen.CodeFile('', str_file)
    comma_separated_strs = ', \n'.join([wrap_u8_sv8(x) for x in translated_strs])
    main_map = cppgen.CppVariable(name=f'{array_name}', type='std::array', is_constexpr=True, initialization_value=f'{{{comma_separated_strs}}}')
    main_map.render_to_string(hpp)
    str_file.seek(0)
    return str_file.read()


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=f"""
Convert PO files to header files\n
Example folder structure (script invoked from locale's parent folder):\n
    Command line arguments: -p locale --pot Example\n
        {emoji.emojize(':open_file_folder:')} locale\n
        ├── {emoji.emojize(':page_facing_up:')} Example.pot\n
        ├── {emoji.emojize(':open_file_folder:')} es_ES\n
        │   └── {emoji.emojize(':page_facing_up:')} Example.po\n
        └── {emoji.emojize(':open_file_folder:')} ja_JA\n
            └── {emoji.emojize(':page_facing_up:')} Example.po\n
Example folder structure (script invoked from locale's parent folder):\n
    Command line arguments: -p locale --pot Example\n
        {emoji.emojize(':open_file_folder:')} locale\n
        ├── {emoji.emojize(':page_facing_up:')} Example.pot\n
        ├── {emoji.emojize(':open_file_folder:')} es_ES\n
        │   └── {emoji.emojize(':page_facing_up:')} Example.po\n
        └── {emoji.emojize(':open_file_folder:')} ja_JA\n
            └── {emoji.emojize(':page_facing_up:')} Example.po""")

    # parser.add_argument('--po',
    #                     help='The input file name | note: This is usually the same name as the .pot file used to generate the .po files',
    #                     required=True)
    # parser.add_argument('--pot',
    #                     help='The input template file name | note: This is usually the same name as the .pot file used to generate the .po files',
    #                     required=True)
    parser.add_argument('--pot',
                        help='The input template file name without the extension | note: This is usually the same name as the .pot file used to generate the .po files',
                        required=True)
    parser.add_argument('-o', '--output',
                        help='The output file name',
                        required=True)
    parser.add_argument('-p', '--path',
                        help='The input folder path',
                        required=True)
    parser.add_argument('-c', '--comment',
                        help='The comment string which indicates the start of a parser specific directive',
                        default='PARSER: ', required=False)
    parser.add_argument('--mapind',
                        help='The comment prefix which indicates that the following string should be the name of the map',
                        default='E18_MAP: ', required=False)
    parser.add_argument('--arrind',
                        help='The comment prefix which indicates that the following string should be the name of the array for the following translatable string',
                        default='E18_ARR: ', required=False)
    parser.add_argument('-e', '--encoding',
                        help='The encoding of the input and output file | eg: utf8',
                        default='utf8', required=False)
    parser.add_argument('--defaultlocale',
                        help='The locale used in the source files (the locale of the strings in the .pot file)',
                        default='en_US', required=False)
    parser.add_argument('--json',
                        help='Export the extracted data in JSON format',
                        action='store_true')
    args = vars(parser.parse_args())

    new_format = new_extract(path=args['path'], pot_name=args['pot'], encoding=args['encoding'], map_indicator=args['mapind'], array_indicator=args['arrind'])

    # gen_translated_array(new_format)

    new_format_file = new_format[args['pot']]

    # languages = OrderedSet(locale for locale in new_format_file['data'])

    # IMPORTANT: It is critical that the order of the locale names in the 'languages' list matches the order of the list in 'translations'
    languages = [args['defaultlocale']] + [locale for locale in new_format_file['data']]  # Generate the list of locales which will be used to access the translated data
    translations = {}
    for key in new_format_file['keys']:  # Generate the list of translations for each word and have the keyword be first
        translations |= {key: [key] + [new_format_file['data'][locale][key] for locale in new_format_file['data']]}

    # for key in new_format_file['keys']:
    #     for locale in new_format_file['data']:
    #         languages.add(locale)
    #         full_data += [key] + new_format_file['data'][locale][key]

        # print([key] + [new_format_file['data'][x][key] for x in new_format_file['data']])

    # print(languages)
    # print(translations)
    translated_arrays = [gen_translated_array(translations[key], new_format_file['array_names'][key]) for key in new_format_file['keys']]
    print(translated_arrays)
    array_names = [new_format_file['array_names'][key] for key in new_format_file['keys']]
    translated_map = gen_translated_map(array_names, new_format_file['map_name'])
    print(translated_map)

    with open(args['output'], 'w', encoding=args['encoding']) as outfile:
        if args['json']:  # If the output will be a json file
            outfile.write(json.dumps(new_format, indent=2))
        else:
            hpp = codegen.CodeFile(args['output'], outfile)
            def_name = args['output'].replace('.', '_').upper()
            hpp(f"#ifndef {def_name}")
            hpp(f"#define {def_name}\n")
            hpp(f"#include <array>")
            hpp(f"#include <string_view>\n")
            hpp(f"#include \"E-I18n/eternalAdapted.hpp\"")
            hpp(f"#include \"E-I18n/ei18n.hpp\"\n")
            hpp("using namespace std::literals::string_view_literals;")
            hpp("using namespace ei18n::literals::string_view_literals;\n")

            for array in translated_arrays:
                hpp(f"{array}")
            hpp(translated_map)

            hpp(f"#endif // {def_name}")


    # print(json.dumps(new_format, indent=2))

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
