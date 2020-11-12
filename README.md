# FacileDesktop
### Версия программы FacileTask для ПК (протестировано только на Линукс)

### Что нового?
* Стабильная и уже юзабельная версия программы

Данная программа является настольной версией FacileTask и находится в разработке. Она будет иметь почти те же функции, что и FacileTask.

### Стек:
* [C](https://ru.wikipedia.org/wiki/%D0%A1%D0%B8_(%D1%8F%D0%B7%D1%8B%D0%BA_%D0%BF%D1%80%D0%BE%D0%B3%D1%80%D0%B0%D0%BC%D0%BC%D0%B8%D1%80%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D1%8F))
* [Gtk](https://www.gtk.org/)
* [Glade (.ui)](https://glade.gnome.org/)

## Установка и удаление
* Скачать скрипт установки с помощью wget. `wget http://188.227.84.204/App/install_linux.sh`
* Запустить скрипт: `sh install_linux.sh`. **Данный файл не помещать в папку FDTar!**
* Для полного удаления скачать скрипт remove_linux.sh. По умолчанию он скачивается при запуске скрипта установки(install_linux.sh). `wget https://raw.githubusercontent.com/SsSha256/FacileDesktop/master/remove_linux.sh`
* Запустить скрипт: `sh remove_linux.sh`

После установки, наберите в консоли: FacileDesktop (/usr/local/bin должен находиться в $PATH).

**Если что-то перестало работать, переустановка всё поправит**
