#!/bin/bash
wget https://github.com/SsSha256/FacileDesktop/releases/download/v.0.2/FDtar.tar.gz2
wget https://raw.githubusercontent.com/SsSha256/FacileDesktop/master/remove_linux.sh
tar -xvf FDtar.tar.gz2
cd FDTar
make
sudo make install
mkdir "$HOME/..Conf"
cd ..
rm -r FDTar FDtar.tar.gz2
