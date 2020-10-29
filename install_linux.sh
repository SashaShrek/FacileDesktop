#!/bin/bash
wget https://github.com/SsSha256/FacileDesktop/releases/download/v.0.1/FDtar.tar.gz2
tar -xvf FDtar.tar.gz2
cd FDTar
make
sudo make install
mkdir "$HOME/Conf"
cd ..
rm -r FDTar FDtar.tar.gz2
