TARGET = FacileDesktop
SRC = bin/FacileDesktop.c bin/AddTask.c bin/OnPass.c bin/OnSync.c bin/Settings.c bin/Pass.c bin/Book.c
#out/MainGUI.ui out/SettingsGUI.ui out/AddTaskGUI.ui out/OnPassGUI.ui out/OnSyncGUI.ui
SRCCLN = out/$(TARGET)
PREFIX = /usr/local/bin

.PHONY: all install uninstall

all: $(TARGET)

$(TARGET): $(SRC)
	gcc $(SRC) -o out/$(TARGET) `pkg-config --cflags --libs gtk+-3.0`

install:
	cp out/$(TARGET) $(PREFIX)/$(TARGET)
	cp ui/*.ui $(PREFIX)/
	cp -r out/Icon $(PREFIX)/Icon
	cp Makefile $(PREFIX)/
	install out/$(TARGET) $(PREFIX)


uninstall:
	rm -rf $(PREFIX)/*.ui $(PREFIX)/$(TARGET) $(PREFIX)/Icon $(PREFIX)/Makefile
