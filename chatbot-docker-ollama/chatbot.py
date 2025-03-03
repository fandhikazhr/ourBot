import requests

# URL API Ollama yang berjalan di dalam container
OLLAMA_API_URL = "http://localhost:11434/api/generate"

def chat_with_bot(prompt):
    response = requests.post(OLLAMA_API_URL, json={"model": "mistral", "prompt": prompt})
    return response.json().get("response", "Terjadi kesalahan.")

print("Chatbot siap! Ketik 'exit' untuk keluar.")
while True:
    user_input = input("Anda: ")
    if user_input.lower() == "exit":
        break
    bot_response = chat_with_bot(user_input)
    print("Bot:", bot_response)

