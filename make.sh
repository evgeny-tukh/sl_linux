#!/bin/bash
#/usr/bin/g++ /home/jeca/work/sl/sl_main.cpp /home/jeca/work/sl/sdk/sl_button.cpp /home/jeca/work/sl/sdk/sl_wnd.cpp /home/jeca/work/sl/sdk/sl_event.cpp /home/jeca/work/sl/sdk/sl_bitmap.cpp /home/jeca/work/sl/sdk/sl_img_button.cpp /home/jeca/work/sl/sl_range_inc_but.cpp /home/jeca/work/sl/sl_range_dec_but.cpp -g -I /home/jeca/work/sl/bin/sl/sdk -std=c++14 -o /home/jeca/work/sl/bin/sl -lX11 -lImlib2
cd /home/jeca/work/sl
cmake -S . -B build -DCMAKE_BUILD_TYPE=$1
cd /home/jeca/work/sl/build
make
