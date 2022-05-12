Microsoft Windows [Version 10.0.19044.1645]
(c) Microsoft Corporation. All rights reserved.

C:\Users\treys>gettext
'gettext' is not recognized as an internal or external command,
operable program or batch file.

C:\Users\treys>cd Code

C:\Users\treys\Code>cd Algae-Standalone

C:\Users\treys\Code\Algae-Standalone>cd firmware

C:\Users\treys\Code\Algae-Standalone\firmware>cd src

C:\Users\treys\Code\Algae-Standalone\firmware\src>xgettext
xgettext: no input file given
Try 'xgettext --help' for more information.

C:\Users\treys\Code\Algae-Standalone\firmware\src>xgettext --language=C --add-comments -o po/main.pot main.cpp

C:\Users\treys\Code\Algae-Standalone\firmware\src>cd ../../../

C:\Users\treys\Code>Embedded-I18n
'Embedded-I18n' is not recognized as an internal or external command,
operable program or batch file.

C:\Users\treys\Code>cd Embedded-I18n

C:\Users\treys\Code\Embedded-I18n>xgettext --language=C --add-comments -o po/main.pot main.cpp
xgettext: cannot create output file "po/main.pot": No such file or directory

C:\Users\treys\Code\Embedded-I18n>xgettext --language=C --add-comments -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=C -c=//. --add-comments -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=C -c=//. --add-comments -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=C -c=//.  --add-comments -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=C -c=//.  --add-comments -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=C -c="//."  --add-comments -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=C -c="//. " --add-comments -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=C -c="//. " -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=C -c="//. " --add-comments -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=C -c=". " --add-comments -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=C -c="#. " --add-comments -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=C -c="#. " --add-comments -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=C --add-comments=#. -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=C --add-comments="#. " -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=C --add-comments="//#. " -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=C --add-comments="#. " -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=C --add-comments=". " -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=c++ --add-comments=". " -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=c++ --add-comments=". " -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=c++ --add-comments="." -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=c++ --add-comments="//." -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=c++ --add-comments="//. " -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=c++ --add-comments=". " -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=c++ --add-comments="/. " -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=c++ --add-comments="/. " -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=c++ --add-comments=". " -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=c++ --add-comments=". " -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=c++ --add-comments="#. " -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=c++ --add-comments="#. " -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=c++ --add-comments="#. " -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=c++ --add-comments="#. " -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=c++ --add-comments -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=c++ --add-comments=/ -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=c++ --add-comments=/ -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=c++ --add-comments="#. " -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>xgettext --language=c++ --add-comments="#. " -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>msginit --input=po/main.pot --locale = es --output=po/main_es.po
msginit: too many arguments

C:\Users\treys\Code\Embedded-I18n>msginit --input=po/main.pot --locale=es --output=po/main_es.po

Created po/main_es.po.

C:\Users\treys\Code\Embedded-I18n>msginit --input=po/main.pot --locale=da --output=po/main_es.po

Created po/main_es.po.

C:\Users\treys\Code\Embedded-I18n>msginit --input=po/main.pot --locale=es --output=po/main_es.po

Created po/main_es.po.

C:\Users\treys\Code\Embedded-I18n>msginit --input=po/main.pot --locale=da --output=po/main_da.po

Created po/main_da.po.

C:\Users\treys\Code\Embedded-I18n>msginit --input=po/main.pot --locale=ja --output=po/main_ja.po

Created po/main_ja.po.

C:\Users\treys\Code\Embedded-I18n>msginit --input=po/main.pot --locale=ja.utf8 --output=po/main_ja.po

Created po/main_ja.po.

C:\Users\treys\Code\Embedded-I18n>msginit --input=po/main.pot --locale=ja.utf8 --output=po/main_ja.po

Created po/main_ja.po.

C:\Users\treys\Code\Embedded-I18n>msginit --input=po/main.pot --locale=ja_JA.UTF-8 --output=po/main_ja.po

Created po/main_ja.po.

C:\Users\treys\Code\Embedded-I18n>xgettext --language=c++ --add-comments="#. " --from-code=UTF-8 -o po/main.pot main.cpp

C:\Users\treys\Code\Embedded-I18n>msginit --input=po/main.pot --locale=ja_JA.UTF-8 --output=po/main_ja.po

Created po/main_ja.po.

C:\Users\treys\Code\Embedded-I18n>msginit --input=po/main.pot --locale=da_DA.UTF-8 --output=po/main_da.po

Created po/main_da.po.

C:\Users\treys\Code\Embedded-I18n>cd PO-Convert

C:\Users\treys\Code\Embedded-I18n\PO-Convert>cd po

C:\Users\treys\Code\Embedded-I18n\PO-Convert\po>msginit --input=po/main.pot --locale=es_ES.UTF-8 --output=po/main_es_ES.po
msginit: error while opening "po/main.pot" for reading: No such file or directory

C:\Users\treys\Code\Embedded-I18n\PO-Convert\po>msginit --input=main.pot --locale=es_ES.UTF-8 --output=po/main_es_ES.po
msginit: cannot create output file "po/main_es_ES.po": No such file or directory

C:\Users\treys\Code\Embedded-I18n\PO-Convert\po>msginit --input=main.pot --locale=es_ES.UTF-8 --output=main_es_ES.po

Created main_es_ES.po.

C:\Users\treys\Code\Embedded-I18n\PO-Convert\po>msginit --input=main.pot --locale=es_ES.UTF-8 --output=main_es_ES_TEST.po

Created main_es_ES_TEST.po.

C:\Users\treys\Code\Embedded-I18n\PO-Convert\po>msginit --input=main.pot --locale=es_ES --output=main_es_ES_TEST.po

Created main_es_ES_TEST.po.

C:\Users\treys\Code\Embedded-I18n\PO-Convert\po>msginit --input=main.pot --locale=ja_JA --output=main_ja.po

Created main_ja.po.

C:\Users\treys\Code\Embedded-I18n\PO-Convert\po>msginit --input=main.pot --locale=ja --output=main_ja.po

Created main_ja.po.

C:\Users\treys\Code\Embedded-I18n\PO-Convert\po>msginit --input=main.pot --locale=es_ES --output=main_es.po

Created main_es.po.

C:\Users\treys\Code\Embedded-I18n\PO-Convert\po>locale - a
'locale' is not recognized as an internal or external command,
operable program or batch file.

C:\Users\treys\Code\Embedded-I18n\PO-Convert\po>