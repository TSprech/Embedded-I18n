import polib
import re
import argparse
import code_generator.code_generator as codegen
import code_generator.cpp_generator as cppgen
import os
from io import StringIO
# import xmltodict
# import requests


def gen_translated_array(translated_strs: list) -> str:
    str_file = StringIO()
    hpp = codegen.CodeFile('', str_file)
    comma_separated_strs = ', '.join([wrap_u8_sv8(x) for x in translated_strs])
    main_map = cppgen.CppVariable(name=f'main_map', type='std::array', is_constexpr=True, initialization_value=f'{{{comma_separated_strs}}}')
    main_map.render_to_string(hpp)
    str_file.seek(0)
    return str_file.read()


def extract_translated(path: str, file_name: str, encoding: str) -> [list, dict]:
    translated_dict = {}
    key_strings = set()
    try:
        for sub_dir in (sub_dir for sub_dir in os.scandir(path) if sub_dir.is_dir()):  # Go through each of the directory items that is a sub directory
            file_path_and_name = f"{path}{sub_dir.name}/{file_name}"
            try:
                po_file = polib.pofile(file_path_and_name, encoding=encoding)  # Open the po file in the directory
                key_strings |= {x.msgid for x in po_file.translated_entries()}
                # Generate the dict of all the translations for the input file name
                translated_dict[sub_dir.name] = {po_file.translated_entries()[i].msgid: po_file.translated_entries()[i].msgstr for i in range(len(po_file.translated_entries()))}
            except IOError:
                print(f"Could not open the po file with the path: {file_path_and_name}")
    except FileNotFoundError:
        print(f"Could not find the folder passed to -p (--path): {args['path']}")  # If the top level directory does not exist
    return list(key_strings), translated_dict


def extract_string_name(parser_indicator, comment_string):
    comment = re.search(parser_indicator + '(.+?)(?:$|\n)', comment_string)  # Get the string between the indicator and a newline or end of string
    return comment.group(1) if comment is not None else ''  # Check that some parser comment was actually extracted


def wrap_u8_sv8(entry: str) -> str:
    return f'u8\"{entry}\"_sv8'


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Convert PO files to header files')
    parser.add_argument('-i', '--input',
                        help='The input file name | note: This is usually the same name as the .pot file used to generate the .po files',
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
                        default='/PARSER: ', required=False)
    parser.add_argument('-e', '--encoding',
                        help='The encoding of the input and output file | eg: utf8',
                        default='utf8', required=False)
    args = vars(parser.parse_args())

    key_strings, translated_data = extract_translated(args['path'], args['input'], args['encoding'])
    # print(key_strings[0])
    # for data in translated_data:
    #     print(translated_data[data][key_strings[0]])

    for i in range(0, len(key_strings)):
        translated_list = [key_strings[i]] + [translated_data[locale][key_strings[i]] for locale in translated_data]
        print(gen_translated_array(translated_list))

    # [wrap_u8_sv8(x.msgstr) for x in pofile.translated_entries()]

    # print(gen_translated_array())

    # print(extract_translated(args['path'], args['input'], args['encoding']))

    # pofile = polib.pofile('po/es_ES/main_es_ES.po', encoding=args['encoding'])
    # print(pofile.metadata['Language'])
    # print(Locales.locales[pofile.metadata['Language']])
    # print(pofile.translated_entries()[1].msgstr)

    # print(wrap_u8_sv8(pofile.translated_entries()[0].msgstr))
    #
    # strings = ', '.join([wrap_u8_sv8(x.msgstr) for x in pofile.translated_entries()])
    #
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
