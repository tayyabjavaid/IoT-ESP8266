#  Author: TAYYAB JAVAID          Date: 2nd, November, 2019, Lahore
#
#  This HOST device program connects to the ESP8266 (ESP-01) Wi-Fi module
#  over the Serial COM port and does the basic setup of the device to run
#  it as a Wi-Fi Client.

#  This code will be further extended to enable HTTP server on the ESP-01,
#  and accept user commands using REST APIs. This is a step in making it
#  a home automation IOT device.
#
#  Block diagram:
#                             AT over
#            -----------    UART SERIAL   -----------
#           |           |       TX       |           |
#           |  HOST     |----------------|           |
#           |  Python   |                | ESP 8266  |
#           |  Program  |       RX       |  (ESP-01) |
#           |           |----------------|           |
#           |           |                |           |
#            -----------                  -----------
#

import serial

## Wi-Fi hotspot
username = "xxxxxx"
password = "xxxxxx"

'''
-----------------------------------------------------------------------
-        Function:            read_serial_resp()
-        Parameters:
-                    handle :        Handle for the open serial
-                               communication channel
-        Return:
-                    string:    String of data received from the serial
-                               channel, terminated on "OK\r\n"
-        Description:
-        Read AT Response terminated on "OK\r\n", on serial channel.
-----------------------------------------------------------------------
'''


def read_serial_resp(handle):
    string = ""
    loop_count = 0
    while (1):
        data = handle.read(50)
        data = str(data)
        string = string + data[2:len(data) - 1]
        if string.count("OK\\r\\n") == 1:
            print("Read Complete ...")
            break
        else:
            if (loop_count > 5):
                break
        loop_count += 1
    return string


if __name__ == '__main__':
    print("Opening Serial over COM7")
    s = serial.serial_for_url("COM7", baudrate=115200, timeout=1)

    ## Send AT #####################################
    print(">>> Sending AT ...")
    s.write("AT\r\n".encode('utf-8'))

    string = read_serial_resp(s)
    print("Read Data: " + string)

    ## Send AT+GMR #####################################
    print(">>> Sending AT+GMR ...")
    s.write("AT+GMR\r\n".encode('utf-8'))

    string = read_serial_resp(s)
    print("Read Data: " + string)

    ## Send AT+CWMODE_DEF #####################################
    print(">>> Sending AT+CWMODE_DEF=1 ...")
    s.write("AT+CWMODE_DEF=1\r\n".encode('utf-8'))

    string = read_serial_resp(s)
    print("Read Data: " + string)

    ## Send AT+CWLAP #####################################
    print(">>> Sending AT+CWLAP ...")
    s.write("AT+CWLAP\r\n".encode('utf-8'))

    string = read_serial_resp(s)
    print("Read Data: " + string)

    ## Send AT+CWJAP #####################################
    print(">>> Sending AT+CWJAP_DEF="+username+","+password+" ...")
    s.write(('AT+CWJAP_DEF=\"{}\",\"{}\"\r\n'.format(username, password)).encode('utf-8'))

    string = read_serial_resp(s)
    print("Read Data: " + string)
    string = read_serial_resp(s)
    print("Read Data: " + string)
    string = read_serial_resp(s)
    print("Read Data: " + string)

    ## Send AT+CIFSR #####################################
    print(">>> Sending AT+CIFSR ...")
    s.write("AT+CIFSR\r\n".encode('utf-8'))

    string = read_serial_resp(s)
    print("Read Data: " + string)

    # Here the string will contain the IP address of the ESP8266
    # Use this IP address to connect to ESP using Web browser or
    # Telnet application.

    # TODO: Parsing of +CIFSR response is required to get the
    #       device IP, to be used later to connect to it.

    ## Send AT+CIPMUX #####################################
    print(">>> Sending AT+CIPMUX=1 ...")
    s.write("AT+CIPMUX=1\r\n".encode('utf-8'))

    string = read_serial_resp(s)
    print("Read Data: " + string)

    ## Send AT+CIPSERVER #####################################
    print(">>> Sending AT+CIPSERVER=1,80 ...")
    s.write("AT+CIPSERVER=1,80\r\n".encode('utf-8'))

    string = read_serial_resp(s)
    print("Read Data: " + string)

    # Open a web browser and ping the IP address of the device
    # A GET request must be received on the serial channel from
    # the web browser. Like received below on channel 0 ...
    #
    #      0, CONNECT
    #      1, CONNECT
    #      
    #      +IPD, 0, 415: GET / HTTP / 1.1
    #      Host: 192.168
    #      .43
    #      .234
    #      Connection: keep - alive
    #      Upgrade - Insecure - Requests: 1
    #      User - Agent: Mozilla / 5.0(Windows
    #      NT
    #      10.0;
    #      Win64;
    #      x64) AppleWebKit / 537.36(KHTML, like
    #      Gecko) Chrome / 78.0
    #      .3904
    #      .87
    #      Safari / 537.36
    #      Accept: text / html, application / xhtml + xml, application / xml;
    #      q = 0.9, image / webp, image / apng, * / *;q = 0.8, application / signed - exchange;
    #      v = b3
    #      Accept - Encoding: gzip, deflate
    #      Accept - Language: en - US, en;
    #      q = 0.9
    #      
    # We send a 5 byte data on channel 0 using the following command...
    #
    #
    #
    #      AT + CIPSEND = 0, 5
    #      
    #      OK
    #      >
    #      Recv
    #      5
    #      bytes
    #      
    #      SEND
    #      OK
    #
    # After sending data, we close the channel 0, like below.
    # This displays the 5 byte data in the browser window used to ping the IP
    # address.
    #
    #      AT + CIPCLOSE = 0
    #      0, CLOSED
    #      
    #      OK
    #      1, CLOSED
    #      0, CONNECT
    #      
    #      +IPD, 0, 350: GET / favicon.ico
    #      HTTP / 1.1
    #      Host: 192.168
    #      .43
    #      .234
    #      Connection: keep - alive
    #      User - Agent: Mozilla / 5.0(Windows
    #      NT
    #      10.0;
    #      Win64;
    #      x64) AppleWebKit / 537.36(KHTML, like
    #      Gecko) Chrome / 78.0
    #      .3904
    #      .87
    #      Safari / 537.36
    #      Accept: image / webp, image / apng, image / *, * / *;q = 0.8
    #      Referer: http: // 192.168
    #      .43
    #      .234 /
    #      Accept - Encoding: gzip, deflate
    #      Accept - Language: en - US, en;
    #      q = 0.9

    print("Closing Serial port")
    s.close()



