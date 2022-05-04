import polib
import re


def extract_string_name(keyword_string, comment_string):
    return re.search(keyword_string + '(.+?)(?:$|\n)', comment_string).group(1)


if __name__ == '__main__':
    pofile = polib.pofile('sample.po')
    print(pofile.translated_entries()[0].encoding)
    parser_comment = pofile.translated_entries()[0].comment
    custom_parser_indicator = "/PARSER: "
    print(extract_string_name(custom_parser_indicator, parser_comment))
    print(pofile.translated_entries()[0].msgstr)
    msg = pofile.translated_entries()[0].msgstr
    print(len(msg))
    msg32 = msg.encode('utf-32')
    # for entry in pofile:
    #     print(entry.msgid, entry.msgstr, entry.msgid_plural, entry.msgstr_plural)
