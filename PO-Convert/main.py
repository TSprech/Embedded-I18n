import polib
import re
import argparse
import code_generator.code_generator as codegen
import code_generator.cpp_generator as cppgen


def extract_string_name(parser_indicator, comment_string):
    comment = re.search(parser_indicator + '(.+?)(?:$|\n)',
                        comment_string)  # Get the string between the indicator and a newline or end of string
    return comment.group(1) if comment is not None else ''  # Check that some parser comment was actually extracted


def wrap_u8_sv8(entry: str) -> str:
    return f'u8\"{entry}\"_sv8'


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Convert PO files to header files')
    parser.add_argument('-c', '--comment',
                        help='The comment string which indicates the start of a parser specific directive',
                        default='/PARSER: ', required=False)
    parser.add_argument('-e', '--encoding',
                        help='The encoding of the input and output file | eg utf8',
                        default='utf8', required=False)
    args = vars(parser.parse_args())

    pofile = polib.pofile('../po/main_da.po', encoding=args['encoding'])
    print(pofile.translated_entries()[0].msgstr)
    print(pofile.translated_entries()[1].msgstr)

    print(wrap_u8_sv8(pofile.translated_entries()[0].msgstr))

    strings = ', '.join([wrap_u8_sv8(x.msgstr) for x in pofile.translated_entries()])

    outfile = open('Example.hpp', 'w', encoding=args['encoding'])
    hpp = codegen.CodeFile('Example.hpp', outfile)
    main_map = cppgen.CppVariable(name='main_map', type='std::array', is_constexpr=True,
                                                        initialization_value=f'{{{strings}}}')
    main_map.render_to_string(hpp)
