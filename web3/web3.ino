

#include <WiFi.h>


#define USE_SERIAL Serial

#define ENV_SSID     "ksaeduap13_2.4G"
#define ENV_WIFI_KEY "1234512345"
#define MY_ADDRESS "0x2AdbE35026547C8107bEF3B039B60FD3c58F53BB"
#define CONTRACT_ADDRESS "0xFdDf9D957B0061a0884Dd2B455fB08917Cbfe861"
#define INFURA_HOST "rinkeby.infura.io"
#define INFURA_PATH "/89715c87a75444e387d6e526e7b8dea8"
//const string INFURA_HOST = "rinkeby.infura.io";
//const string INFURA_PATH = "";

const char PRIVATE_KEY[] = {0x9E,0x41,0x50,0x2E,0xAC,0x1E,0x8C,0x00,
                            0xAD,0x62,0x23,0x9D,0x19,0x52,0x70,0x98,
                            0xBF,0xD2,0x58,0x30,0x3E,0xF2,0x18,0x05,
                            0xC7,0xE9,0xE5,0x25,0x3C,0xF9,0xBF,0x1B };

Web3 web3();

void eth_send_example();

void setup() {
    USE_SERIAL.begin(115200);

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    WiFi.begin(ENV_SSID, ENV_WIFI_KEY);

    // attempt to connect to Wifi network:
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        // wait 1 second for re-trying
        delay(1000);
    }

    USE_SERIAL.println("Connected");

    eth_send_example();
}

void loop() {
    // put your main code here, to run repeatedly:
}

void eth_send_example() {
    Contract contract(&web3, CONTRACT_ADDRESS);
    contract.SetPrivateKey((uint8_t*)PRIVATE_KEY);
    uint32_t nonceVal = (uint32_t)web3.EthGetTransactionCount((char *)MY_ADDRESS);

    uint32_t gasPriceVal = 141006540;
    uint32_t  gasLimitVal = 3000000;
    uint8_t toStr[] = CONTRACT_ADDRESS;
    uint8_t valueStr[] = "0x00";
    uint8_t dataStr[100];
    memset(dataStr, 0, 100);
    string func = "set(uint256)";
    string p = contract.SetupContractData(&func, 123);
    string result = contract.SendTransaction(nonceVal, gasPriceVal, gasLimitVal, &toStr, &valueStr, &p);

    USE_SERIAL.println(result);
}
