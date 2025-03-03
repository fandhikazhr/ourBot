import json
import numpy as np
from gensim.models import Word2Vec
from sklearn.metrics.pairwise import cosine_similarity
from rich.console import Console

console = Console()

DB_FILE = "chatbot_data.json"

# Load database dari JSON
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

# Buat dataset untuk Word2Vec
sentences = [q.lower().split() for q in conversations.keys()]
model = Word2Vec(sentences, vector_size=100, window=5, min_count=1, workers=4)

def sentence_vector(sentence):
    """Mengubah kalimat menjadi vektor dengan Word2Vec"""
    words = sentence.lower().split()
    vectors = [model.wv[word] for word in words if word in model.wv]
    return np.mean(vectors, axis=0) if vectors else np.zeros(100)

def chatbot_response(user_input):
    global model  

    user_vec = sentence_vector(user_input)
    best_match = None
    best_score = -1

    for question in conversations.keys():
        q_vec = sentence_vector(question)
        score = cosine_similarity([user_vec], [q_vec])[0, 0]

        if score > best_score:
            best_score = score
            best_match = question

    # Jika kemiripan cukup tinggi
    THRESHOLD = 0.6
    if best_score >= THRESHOLD:
        return conversations[best_match]

    console.print("\n[bold red]Bot:[/] Saya belum tahu jawabannya. Apa jawaban yang benar?")
    new_response = input("You (jawaban): ")

    # Simpan pertanyaan baru ke database
    conversations[user_input] = new_response
    with open(DB_FILE, "w") as f:
        json.dump(conversations, f, indent=4)

    # Update model Word2Vec
    sentences.append(user_input.lower().split())
    model.build_vocab(sentences, update=True)
    model.train(sentences, total_examples=len(sentences), epochs=10)

    return "Terima kasih! Saya akan mengingat ini."

# Jalankan chatbot
console.print("[bold green]Chatbot siap digunakan! Ketik 'exit' untuk keluar.[/]")
while True:
    user_input = input("\nYou: ")
    if user_input.lower() == "exit":
        break
    console.print(f"[bold blue]Bot:[/] {chatbot_response(user_input)}")

