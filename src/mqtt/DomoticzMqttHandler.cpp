#include "DomoticzMqttHandler.h"
#include "web/root/domoticz_json.h"

bool DomoticzMqttHandler::publish(AmsData* data, AmsData* previousState) {
    bool ret = false;
    if (config.elidx > 0) {
        if(data->getActiveImportCounter() > 1.0) {
            energy = data->getActiveImportCounter();
        }
        if(energy > 0.0) {
            char val[16];
            snprintf(val, 16, "%.1f;%.1f", (data->getActiveImportPower()/1.0), energy*1000.0);
            char json[192];
            snprintf_P(json, sizeof(json), DOMOTICZ_JSON,
                config.elidx,
                val
            );
            ret = mqtt->publish("domoticz/in", json);
        }
    }

    if(data->getListType() == 1)
        return ret;

    if (config.vl1idx > 0){				
        if (data->getL1Voltage() > 0.1){ 
            char val[16];
            snprintf(val, 16, "%.2f", data->getL1Voltage());
            char json[192];
            snprintf_P(json, sizeof(json), DOMOTICZ_JSON,
                config.vl1idx,
                val
            );
            ret |= mqtt->publish("domoticz/in", json);
        }
    }

    if (config.vl2idx > 0){				
        if (data->getL2Voltage() > 0.1){ 
            char val[16];
            snprintf(val, 16, "%.2f", data->getL2Voltage());
            char json[192];
            snprintf_P(json, sizeof(json), DOMOTICZ_JSON,
                config.vl2idx,
                val
            );
            ret |= mqtt->publish("domoticz/in", json);
        }
    }

    if (config.vl3idx > 0){				
        if (data->getL3Voltage() > 0.1){ 
            char val[16];
            snprintf(val, 16, "%.2f", data->getL3Voltage());
            char json[192];
            snprintf_P(json, sizeof(json), DOMOTICZ_JSON,
                config.vl3idx,
                val
            );
            ret |= mqtt->publish("domoticz/in", json);
        }
    }

    if (config.cl1idx > 0){				
        if(data->getL1Current() > 0.0) {
            char val[16];
            snprintf(val, 16, "%.1f;%.1f;%.1f", data->getL1Current(), data->getL2Current(), data->getL3Current());
            char json[192];
            snprintf_P(json, sizeof(json), DOMOTICZ_JSON,
                config.cl1idx,
                val
            );
            ret |= mqtt->publish("domoticz/in", json);
        }
    }			
    return ret;
}

bool DomoticzMqttHandler::publishTemperatures(AmsConfiguration* config, HwTools* hw) {
    return false;
}

bool DomoticzMqttHandler::publishPrices(EntsoeApi* eapi) {
    return false;
}

bool DomoticzMqttHandler::publishSystem(HwTools* hw) {
    return false;
}
