import argparse
import copy

import requests
import xmltodict

parser = argparse.ArgumentParser(description = 'Convert PO files to header files')
# parser.add_argument('-u', '--url',
#                     help = 'The url to the "main" folder in the cldr repo',
#                     required = True)
parser.add_argument('-p', '--path',
                    help = 'The path to the "main" folder in the cldr download',
                    required = True)
parser.add_argument('-l', '--locale',
                    help = 'The locale name',
                    required = True)
args = vars(parser.parse_args())

# url = args['url']
path = args['path']
locale_full = args['locale']
language = args['locale'].split('_')[0]  # Get the language from the first couple letters before the underscore in the locale name


class Infix:
    def __init__(self, function):
        self.function = function

    def __ror__(self, other):
        return Infix(lambda x, self = self, other = other: self.function(other, x))

    def __or__(self, other):
        return self.function(other)

    def __rlshift__(self, other):
        return Infix(lambda x, self = self, other = other: self.function(other, x))

    def __rshift__(self, other):
        return self.function(other)

    def __call__(self, value1, value2):
        return self.function(value1, value2)


with open(f'{path}/{language}.xml', 'rb') as general_locale:
    general_locale_map = xmltodict.parse(general_locale, encoding = 'UTF-8', xml_attribs = True)['ldml']
    with open(f'{path}/{locale_full}.xml', 'rb') as specific_locale:
        specific_locale_map = xmltodict.parse(specific_locale, encoding = 'UTF-8', xml_attribs = True)['ldml']

        # # print(specific_locale_map["dates"]["calendars"]["calendar"]["@type"])
        # try:
        #     print(specific_locale_map["numbers"]["symbols"]["decimal"])
        #     print("^ Found in specific")
        # except KeyError:
        #     print(general_locale_map["numbers"]["symbols"]["decimal"])
        #     print("^ Found in general")
        #
        # try:
        #     print(specific_locale_map["numbers"]["symbols"])
        #     print("^ Found in specific")
        # except KeyError:
        #     print(general_locale_map["numbers"]["symbols"])
        #     print("^ Found in general")
        #
        # try:
        #     print(specific_locale_map["numbers"])
        #     print("^ Found in specific")
        # except KeyError:
        #     print(general_locale_map["numbers"])
        #     print("^ Found in general")

        # def remove_levels(in_dict, keys_to_remove):
        #     try:
        #         result = {}
        #         for key, value in in_dict.items():
        #             if key in keys_to_remove:
        #                 result = {**result, **remove_levels(value, keys_to_remove)}
        #             else:
        #                 result[key] = remove_levels(value, keys_to_remove)
        #         return result
        #     except AttributeError:
        #         return in_dict
        #
        #
        # # items = {y: x for x, y in general_locale_map["dates"]["calendars"]["calendar"][0].items()}
        # items = copy.deepcopy(general_locale_map["dates"]["calendars"]["calendar"][0])
        # items.pop('@type')
        # items2 = {general_locale_map["dates"]["calendars"]["calendar"][0]['@type']: items}
        # # items = {{y: x} for x, y in general_locale_map["dates"]["calendars"]["calendar"][0].items()}
        # # for point in range(0, len(general_locale_map["dates"]["calendars"]["calendar"])):
        # #     general_locale_map["dates"]["calendars"]["calendar"][point] = {y: x for x, y in general_locale_map["dates"]["calendars"]["calendar"][point].items()}
        #
        # print(items)
        # print(items2)

        # gregorian_calendar_data = next((item for item in general_locale_map["dates"]["calendars"]["calendar"] if item["@type"] == "gregorian"), None)
        # calendar_days = next((item for item in gregorian_calendar_data["days"]["dayContext"] if item["@type"] == "stand-alone"), None)
        # name_days = next((item for item in calendar_days["dayWidth"] if item["@type"] == "narrow"), None)
        # print(name_days)

        # x = Infix(lambda x, y: x * y)
        # print(2 | x | 4)

        x = Infix(lambda data, attrib: next((item for item in data if item[list(item.keys())[0]] == attrib), None))
        print(((((general_locale_map["dates"]["calendars"]["calendar"] | x | "gregorian")['months']['monthContext'] | x | "stand-alone")['monthWidth'])['month'] | x | "1")['#text'])

        def find_locale_point(data, *argv):
            temp_point = data
            for arg in argv:
                if arg[0] == '@':
                    temp_point = next((item for item in temp_point if item[list(item.keys())[0]] == arg[1:]), None)
                else:
                    temp_point = temp_point[arg]
            return temp_point

        print(find_locale_point(general_locale_map, 'dates', 'calendars', 'calendar', '@gregorian', 'months', 'monthContext', '@stand-alone', 'monthWidth', 'month', '@1', '#text'))

        # gregorian_calendar_data = next((item for item in general_locale_map["dates"]["calendars"]["calendar"] if item["@type"] == "gregorian"), None)
        # calendar_days = next((item for item in gregorian_calendar_data["days"]["dayContext"] if item["@type"] == "stand-alone"), None)
        # name_days = next((item for item in calendar_days["dayWidth"] if item["@type"] == "narrow"), None)
        # print(name_days)

# with requests.get(f'{url}/{language}.xml') as general_locale:
#     general_locale_map = xmltodict.parse(general_locale.text, encoding='UTF-8')['ldml']
#     with requests.get(f'{url}/{locale_full}.xml') as specific_locale:
#         specific_locale_map = xmltodict.parse(specific_locale.text, encoding = 'UTF-8')['ldml']
#         # print(xmltodict.parse(specific_locale.text, encoding = 'UTF-8'))
#         full_locale = general_locale_map | specific_locale_map
