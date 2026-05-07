#include <bits/stdc++.h>
#include <curl/curl.h>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

size_t writeCallback(void* ptr, size_t size, size_t nmemb, string* data) {
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

json getPage(int page) {
    CURL* curl = curl_easy_init();
    string response;
    string url = "https://jsonmock.hackerrank.com/api/articles?page=" + to_string(page);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return json::parse(response);
}

vector<string> topArticles(int limit) {
    vector<pair<int, string>> articles;

    json first = getPage(1);
    int totalPages = first["total_pages"];

    for (int p = 1; p <= totalPages; p++) {
        json page = (p == 1) ? first : getPage(p);
        for (auto& item : page["data"]) {
            string name;
            if (!item["title"].is_null()) name = item["title"];
            else if (!item["story_title"].is_null()) name = item["story_title"];
            else continue;

            int comments = item["num_comments"].is_null() ? 0 : (int)item["num_comments"];
            articles.push_back({comments, name});
        }
    }

    sort(articles.begin(), articles.end(), [](auto& a, auto& b) {
        return a.first != b.first ? a.first > b.first : a.second > b.second;
    });

    vector<string> result;
    for (int i = 0; i < limit && i < articles.size(); i++)
        result.push_back(articles[i].second);
    return result;
}

int main() {
    int limit;
    std::printf("Enter the number of top articles to display: ");
    cin >> limit;
    for (auto& name : topArticles(limit))
        cout << name << "\n";
}