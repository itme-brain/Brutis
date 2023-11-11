#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bip39.h>
#include <curl/curl.h>
#include <json-c/json.h>

// Function to generate a random seed phrase
void generateSeedPhrase(int seedLength, char finalSeedPhrase[][11]) {
  for (int i = 0; i < seedLength; ++i) {
    // Generate a random index for BIP39 word list
    int wordIndex = rand() % MAX_WORDLIST_INDEX;
    // Copy the word from BIP39 word list to final seed phrase
    strcpy(finalSeedPhrase[i], bip39WordList[wordIndex]);
  }
}

// Function to send JSON-RPC request
void send_json_rpc_request(const char* node_url, const char* payload) {
  CURL *curl = curl_easy_init();
  if(curl) {
    // Set the URL for the RPC endpoint
    curl_easy_setopt(curl, CURLOPT_URL, node_url);

    // Specify the POST data
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload);

    // Perform the request, res will get the return code
    CURLcode res = curl_easy_perform(curl);

    // Check for errors
    if(res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }

    // Always cleanup
    curl_easy_cleanup(curl);
  }
}

int main() {
  // Initialize random number generator
  srand(time(NULL));


  // Simulate flipping a coin
  int seedLength = (rand() % 2 == 0)
    ? 12 
    : 24;

  // Initialize the finalSeedPhrase
  char finalSeedPhrase[24][11]; // Assuming each word can be up to 10 characters plus null terminator

  // Generate the seed phrase
  generateSeedPhrase(seedLength, finalSeedPhrase);

  // Print the seed phrase (for demonstration purposes; in practice, be careful with logging sensitive information)
  printf("Seed Phrase: ");
  for (int i = 0; i < seedLength; ++i) {
    printf("%s ", finalSeedPhrase[i]);
  }
  printf("\n");

  // The URL of the Ethereum node
  const char* node_url = "http://localhost:8545";

  // The JSON-RPC Payload
  const char* payload =
    "{"
    "  \"jsonrpc\":\"2.0\","
    "  \"method\":\"eth_getBalance\","
    "  \"params\":[\"0xAddress\", \"latest\"],"
    "  \"id\":1"
    "}";

  // Send the request
  send_json_rpc_request(node_url, payload);

  return 0;
}
