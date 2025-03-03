import json
import random
from rich.console import Console
from rich.text import Text
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity

# Inisialisasi Rich Console
console = Console()

# File database chatbot
DB_FILE = "chatbot_data.json"

# Load database jika ada, jika tidak buat baru
try:
    with open(DB_FILE, "r") as f:
        conversations = json.load(f)
except FileNotFoundError:
    conversations = {
        "halo": "Hai! Ada yang bisa saya bantu?",
        "siapa namamu?": "Saya adalah chatbot sederhana.",
        "apa kabar?": "Saya baik, terima kasih! Bagaimana denganmu?",
        "terima kasih": "Sama-sama! Senang bisa membantu."
    }

# Buat TF-IDF Vectorizer
vectorizer = TfidfVectorizer()
X = vectorizer.fit_transform(conversations.keys())

def chatbot_response(user_input):
    global X, vectorizer  # Supaya bisa diperbarui
    user_vec = vectorizer.transform([user_input])
    similarities = cosine_similarity(user_vec, X)
    best_match = similarities.argmax()

    # Jika ada pertanyaan yang mirip di database
    if similarities[0, best_match] > 0.3:
        return list(conversations.values())[best_match]
    
    # Jika tidak ada, chatbot belajar dari user
    console.print("\n[bold red]Bot:[/] Saya belum tahu jawabannya. Apa jawaban yang benar?")
    new_response = input("You (jawaban): ")

    # Simpan ke database
    conversations[user_input] = new_response
    with open(DB_FILE, "w") as f:
        json.dump(conversations, f, indent=4)

    # Update model TF-IDF
    vectorizer = TfidfVectorizer()
    X = vectorizer.fit_transform(conversations.keys())

    return "Terima kasih! Saya akan mengingat ini."

# Jalankan chatbot di terminal dengan warna
while True:
    console.print("\n[bold cyan]You:[/] ", end="")
    user_input = input()
    if user_input.lower() == "exit":
        console.print("[bold red]Bot:[/] Sampai jumpa!")
        break
    response = chatbot_response(user_input)
    console.print(f"[bold green]Bot:[/] {response}")

