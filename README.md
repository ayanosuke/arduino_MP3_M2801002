# arduino_MP3_M2801002
aitendoで売っている極小MP3モジュール [M2801002]をArduinoから動かします。(The aitendo tiny MP3 module is controlled [M2801002] by Arduino.)

極小MP3モジュール [M2801002]　http://www.aitendo.com/product/11667
は、抵抗値で動作モードを決定するADKEYという機能を使用していますが、
そのADKEY端子にArduinoのPWM出力にLPF通した信号を接続して、制御してみました。
Arduino IDE 1.6.5 for Mac にて、作成しました。

http://atmel.client.jp/m2801022.html
