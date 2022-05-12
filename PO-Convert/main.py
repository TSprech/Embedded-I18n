import polib
import re
import argparse
import code_generator.code_generator as codegen
import code_generator.cpp_generator as cppgen
import os
import xmltodict

import Locales


def extract_string_name(parser_indicator, comment_string):
    comment = re.search(parser_indicator + '(.+?)(?:$|\n)',
                        comment_string)  # Get the string between the indicator and a newline or end of string
    return comment.group(1) if comment is not None else ''  # Check that some parser comment was actually extracted


def wrap_u8_sv8(entry: str) -> str:
    return f'u8\"{entry}\"_sv8'


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Convert PO files to header files')
    parser.add_argument('-o', '--output',
                        help='The output file name',
                        required=False)  # TODO: Make required
    parser.add_argument('-p', '--path',
                        help='The input folder path',
                        required=False)  # TODO: Make required
    parser.add_argument('-c', '--comment',
                        help='The comment string which indicates the start of a parser specific directive',
                        default='/PARSER: ', required=False)
    parser.add_argument('-e', '--encoding',
                        help='The encoding of the input and output file | eg utf8',
                        default='utf8', required=False)
    args = vars(parser.parse_args())

    # directory = os.scandir(args['path'])
    # for file in directory:
    #     if file.is_file() and file.path.endswith('.po'):
    #         print(file.name)
    # directory.close()

    pofile = polib.pofile('po/es_ES/main_es_ES.po', encoding=args['encoding'])
    print(pofile.metadata['Language'])
    print(Locales.locales[pofile.metadata['Language']])
    print(pofile.translated_entries()[1].msgstr)

    # print(wrap_u8_sv8(pofile.translated_entries()[0].msgstr))
    #
    # strings = ', '.join([wrap_u8_sv8(x.msgstr) for x in pofile.translated_entries()])
    #
    # outfile = open('Example.hpp', 'w', encoding=args['encoding'])
    # hpp = codegen.CodeFile('Example.hpp', outfile)
    # main_map = cppgen.CppVariable(name='main_map', type='std::array', is_constexpr=True,
    #                                                     initialization_value=f'{{{strings}}}')
    # main_map.render_to_string(hpp)

    with open("cldr/41.0/common/main/en.xml", 'rb') as file:
        xml_dict = xmltodict.parse(file, encoding='UTF-8')['ldml']
        print(xml_dict["numbers"]["symbols"]["decimal"])
        print(xml_dict["numbers"]["symbols"]["group"])
        print(xml_dict["numbers"]["symbols"])
        file.close()

    # with open("cldr/41.0/common/main/en.xml", encoding='UTF-8') as file:
    #     for event, element in ET.iterparse(file, ["start"]):
    #         print(element.tag, " | ", element.text)
