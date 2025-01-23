#include "../../Cheat.h"
#include "../../../ext/Curl/curl.h"

bool fetched = false;

using json = nlohmann::json;
using PlayerMap = std::unordered_map<int, std::string>;


size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

PlayerMap fetchPlayerInfo(const std::string& C_ID) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    PlayerMap PlayerIdToName;


    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://servers-frontend.fivem.net/api/servers/single/" + C_ID;
        std::cout << "Fetching URL: " << url << std::endl;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7");
        headers = curl_slist_append(headers, "accept-language: en-GB,en-US;q=0.9,en;q=0.8");
        headers = curl_slist_append(headers, "cache-control: max-age=0");
        headers = curl_slist_append(headers, "cookie: OptanonAlertBoxClosed=2024-11-24T23:31:17.005Z; OptanonConsent=isGpcEnabled=0&datestamp=Thu+Dec+05+2024+02%3A26%3A10+GMT%2B0000+(Greenwich+Mean+Time)&version=202402.1.0&browserGpcFlag=0&isIABGlobal=false&hosts=&genVendors=&consentId=26ff02d4-7ff2-47ec-808c-d8d9de05303f&interactionCount=2&isAnonUser=1&landingPath=NotLandingPage&groups=1%3A1%2C2%3A0%2C3%3A0%2C4%3A0&geolocation=GB%3BENG&AwaitingReconsent=false; cf_clearance=LGbcj6Ry8gwGOtel8_iBf7qPDdqnH2Rnoj18OzF3GsM-1733914850-1.2.1.1-7XJGOlbs5IfCqxFv87LQEOzTl4v0tbVfJs8HLJkJWKbLXPoN45skakxnK04sS743JCC9A5J4jfbInRn57G26ulZu2qpVmupiJ321OgnKqb6SDZF9L8sc_X.XgNEX34pFpIqdWccYl7RJSMfoyE_3EjRSjSlBiwHV9rfjUV046980OHAW_lVHesfySKSmHgMV1Ye4wpcocqZS76f8ASUO8RKs8aDkNBEEyiSI41DKO2fcgJQZoB58mUfzsy64_NV31aNOq568nxKySBRvIxjMeXDKEIcaSUT8jxeQ9uGo8k5gysUrRhOPz1wd21C6.almfppXmA3D_lVPTGr5_72OM_Gb7N4RAmTODDht.xpNgGTg0TB.7KL5R_rGzDMvE1rpH6KyOhzgflvtP8d5Ls1HghsAG35cmK9qjDrba6B32gcY5FqSwD0kVTqeh8CR7WTx");
        headers = curl_slist_append(headers, "priority: u=0, i");
        headers = curl_slist_append(headers, "sec-ch-ua: \"Google Chrome\";v=\"131\", \"Chromium\";v=\"131\", \"Not_A Brand\";v=\"24\"");
        headers = curl_slist_append(headers, "sec-ch-ua-mobile: ?0");
        headers = curl_slist_append(headers, "sec-ch-ua-platform: \"Windows\"");
        headers = curl_slist_append(headers, "sec-fetch-dest: document");
        headers = curl_slist_append(headers, "sec-fetch-mode: navigate");
        headers = curl_slist_append(headers, "sec-fetch-site: none");
        headers = curl_slist_append(headers, "sec-fetch-user: ?1");
        headers = curl_slist_append(headers, "upgrade-insecure-requests: 1");
        headers = curl_slist_append(headers, "user-agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/131.0.0.0 Safari/537.36");

        // Set the headers
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Request failed: " << curl_easy_strerror(res) << std::endl;
        }
        else {
            // Parse JSON response
            json ServerInfo = json::parse(readBuffer);
            //std::cout << ServerInfo << std::endl;
            for (const auto& Player : ServerInfo["Data"]["players"]) {
                PlayerIdToName[Player["id"]] = Player["name"];
            }
        }

        curl_easy_cleanup(curl);
    }
    else {
        std::cerr << "Failed to initialize CURL." << std::endl;
    }

    return PlayerIdToName;
}

PlayerMap sigma;
std::string NameESP;

void Cheat::Names(CPed *pEntity, float pBottom, Vector2 pBase) {
    char buffer[256];

    if (!fetched) {
        m.ReadString(m.GetModuleBase("glue.dll") + 0x1ea168, buffer, sizeof(buffer));
        std::cout << buffer << std::endl;
        sigma = fetchPlayerInfo(buffer);
        std::cout << "Finished Sigma Operation" << std::endl;
        fetched = true;
    }
    if (fetched) {
        g.PM = sigma;
        for (const auto& [id, name] : sigma) {
            if (pEntity->m_fID == id) {
                //   std::cout << "Player ID: " << id << ", Name: " << name << std::endl;
                NameESP = name + ":" + std::to_string(id);
                String(ImVec2(pBase.x - ImGui::CalcTextSize(NameESP.c_str()).x / 2.f, pBottom + 10.f), ImColor(1.f, 1.f, 1.f, 1.f), NameESP.c_str());

                // std::cout << ++i << std::endl;
            }
        }
    }
}