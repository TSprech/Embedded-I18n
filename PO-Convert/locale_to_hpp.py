import argparse
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


with open(f'{path}/{language}.xml', 'rb') as general_locale:
    general_locale_map = xmltodict.parse(general_locale, encoding='UTF-8', xml_attribs=True)['ldml']
    with open(f'{path}/{locale_full}.xml', 'rb') as specific_locale:
        specific_locale_map = xmltodict.parse(specific_locale, encoding = 'UTF-8', xml_attribs=True)['ldml']
        # print(specific_locale_map["dates"]["calendars"]["calendar"]["@type"])
        try:
            print(specific_locale_map["numbers"]["symbols"]["decimal"])
            print("^ Found in specific")
        except KeyError:
            print(general_locale_map["numbers"]["symbols"]["decimal"])
            print("^ Found in general")

        try:
            print(specific_locale_map["numbers"]["symbols"])
            print("^ Found in specific")
        except KeyError:
            print(general_locale_map["numbers"]["symbols"])
            print("^ Found in general")

        try:
            print(specific_locale_map["numbers"])
            print("^ Found in specific")
        except KeyError:
            print(general_locale_map["numbers"])
            print("^ Found in general")

        gregorian_calendar_data = next((item for item in general_locale_map["dates"]["calendars"]["calendar"] if item["@type"] == "gregorian"), None)
        calendar_days = next((item for item in gregorian_calendar_data["days"]["dayContext"] if item["@type"] == "stand-alone"), None)
        name_days = next((item for item in calendar_days["dayWidth"] if item["@type"] == "narrow"), None)
        print(name_days)

# with requests.get(f'{url}/{language}.xml') as general_locale:
#     general_locale_map = xmltodict.parse(general_locale.text, encoding='UTF-8')['ldml']
#     with requests.get(f'{url}/{locale_full}.xml') as specific_locale:
#         specific_locale_map = xmltodict.parse(specific_locale.text, encoding = 'UTF-8')['ldml']
#         # print(xmltodict.parse(specific_locale.text, encoding = 'UTF-8'))
#         full_locale = general_locale_map | specific_locale_map
