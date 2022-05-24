import argparse

# import requests
import re

import xmltodict


def find_locale_point(data, *argv):
    for file in data:
        try:  # Try to find the data in more specific files and move to more general files in accordance with the search_order list
            result = file  # Result will be the value found at the specified XML category
            for arg in argv:
                if arg[0] == '@':  # A string starting with an @ sign means that it is an attribute, so a search must be done to see where it is
                    key, attr = arg.split('=')
                    if isinstance(result, list):
                        result = next((item for item in result if item[key] == attr), None)  # Find the dictionary which contains the attribute value
                    # If it is already a dict, do nothing, as there is no need to iterate through multiple lists to see which one has the right attribute
                else:
                    try:
                        result = result[arg]  # If it is not an attribute, then it is likely a dictionary, so it can just be indexed into
                    except TypeError:
                        raise KeyError  # If however it was not a dictionary, then there is some other issue (most likely not a locale specific entry for it) so skip to the next search level
            return result  # If it successfully completed the above for loop, then the data was found and it can be returned
        except KeyError:
            continue


parser = argparse.ArgumentParser(description='Convert PO files to header files')
# parser.add_argument('-u', '--url',
#                     help = 'The url to the "main" folder in the cldr repo',
#                     required = True)
parser.add_argument('-p', '--path',
                    help='The path to the "main" folder in the cldr download',
                    required=True)
parser.add_argument('-l', '--locale',
                    help='The locale name',
                    required=True)
args = vars(parser.parse_args())

# url = args['url']
path = args['path']
locale_full = args['locale']
language = args['locale'].split('_')[0]  # Get the language from the first couple letters before the underscore in the locale name

locale_full = "ja_JP"
language = "ja"

with open(f'{path}/{language}.xml', 'rb') as general_locale:
    general_locale_map = xmltodict.parse(general_locale, encoding='UTF-8', xml_attribs=True)['ldml']
    with open(f'{path}/{locale_full}.xml', 'rb') as specific_locale:
        specific_locale_map = xmltodict.parse(specific_locale, encoding='UTF-8', xml_attribs=True)['ldml']
        search_order = [specific_locale_map, general_locale_map]

        # print(find_locale_point(search_order, 'delimiters', 'quotationStart'))
        # print(find_locale_point(search_order, 'delimiters', 'quotationEnd'))
        # print(find_locale_point(search_order, 'delimiters', 'alternateQuotationStart'))
        # print(find_locale_point(search_order, 'delimiters', 'alternateQuotationEnd'))
        # print(find_locale_point(search_order, 'numbers', 'symbols', '@numberSystem=latn', 'decimal'))
        # print(find_locale_point(search_order, 'numbers', 'symbols', '@numberSystem=latn', 'group'))
        # print(find_locale_point(search_order, 'numbers', 'symbols', '@numberSystem=latn', 'list'))
        # print(find_locale_point(search_order, 'numbers', 'symbols', '@numberSystem=latn', 'percentSign'))
        # print(find_locale_point(search_order, 'numbers', 'symbols', '@numberSystem=latn', 'plusSign'))
        # print(find_locale_point(search_order, 'numbers', 'symbols', '@numberSystem=latn', 'minusSign'))
        # print(find_locale_point(search_order, 'numbers', 'symbols', '@numberSystem=latn', 'exponential'))
        # print(find_locale_point(search_order, 'numbers', 'symbols', '@numberSystem=latn', 'superscriptingExponent'))
        # print(find_locale_point(search_order, 'numbers', 'symbols', '@numberSystem=latn', 'infinity'))
        # print(find_locale_point(search_order, 'numbers', 'symbols', '@numberSystem=latn', 'nan'))
        # print(find_locale_point(search_order, 'dates', 'calendars', 'calendar', '@type=gregorian', 'days', 'dayContext', '@type=format', 'dayWidth', '@type=abbreviated', 'day', '@type=sun', '#text'))
        # print(find_locale_point(search_order, 'dates', 'calendars', 'calendar', '@type=gregorian', 'days', 'dayContext', '@type=format', 'dayWidth', '@type=abbreviated', 'day', '@type=mon', '#text'))
        # print(find_locale_point(search_order, 'dates', 'calendars', 'calendar', '@type=gregorian', 'days', 'dayContext', '@type=format', 'dayWidth', '@type=abbreviated', 'day', '@type=tue', '#text'))
        # print(find_locale_point(search_order, 'dates', 'calendars', 'calendar', '@type=gregorian', 'days', 'dayContext', '@type=format', 'dayWidth', '@type=abbreviated', 'day', '@type=wed', '#text'))
        # print(find_locale_point(search_order, 'dates', 'calendars', 'calendar', '@type=gregorian', 'days', 'dayContext', '@type=format', 'dayWidth', '@type=abbreviated', 'day', '@type=thu', '#text'))
        # print(find_locale_point(search_order, 'dates', 'calendars', 'calendar', '@type=gregorian', 'days', 'dayContext', '@type=format', 'dayWidth', '@type=abbreviated', 'day', '@type=fri', '#text'))
        # print(find_locale_point(search_order, 'dates', 'calendars', 'calendar', '@type=gregorian', 'days', 'dayContext', '@type=format', 'dayWidth', '@type=abbreviated', 'day', '@type=sat', '#text'))
        # print(find_locale_point(search_order, 'dates', 'calendars', 'calendar', '@type=gregorian', 'dayPeriods', 'dayPeriodContext', '@type=stand-alone', 'dayPeriodWidth', '@type=abbreviated',
        #                         'dayPeriod', '@type=am', '#text'))
        # print(find_locale_point(search_order, 'dates', 'calendars', 'calendar', '@type=gregorian', 'dayPeriods', 'dayPeriodContext', '@type=stand-alone', 'dayPeriodWidth', '@type=abbreviated',
        #                         'dayPeriod', '@type=pm', '#text'))
        # print(find_locale_point(search_order, 'dates', 'calendars', 'calendar', '@type=gregorian', 'timeFormats', 'timeFormatLength', '@type=medium', 'timeFormat', 'pattern'))
        # print(find_locale_point(search_order, 'dates', 'calendars', 'calendar', '@type=gregorian', 'timeFormats', 'timeFormatLength', '@type=short', 'timeFormat', 'pattern'))

        test_file = open('HeaderFormatter', 'r')
        for str_line in test_file.readlines():
            directives = re.findall(r"(?<=~).+?(?=~)", str_line)[0]
            composition = f"found_char = find_locale_point(search_order, {directives})"
            exec(composition)
            var_name = re.findall(r".+?(?=~)", str_line)[0]
            full_line = var_name + str(found_char)
            print(full_line)

        # print(value)

# with requests.get(f'{url}/{language}.xml') as general_locale:
#     general_locale_map = xmltodict.parse(general_locale.text, encoding='UTF-8')['ldml']
#     with requests.get(f'{url}/{locale_full}.xml') as specific_locale:
#         specific_locale_map = xmltodict.parse(specific_locale.text, encoding = 'UTF-8')['ldml']
#         # print(xmltodict.parse(specific_locale.text, encoding = 'UTF-8'))
#         full_locale = general_locale_map | specific_locale_map
