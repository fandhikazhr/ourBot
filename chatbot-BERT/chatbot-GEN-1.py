import json
import numpy as np
from sentence_transformers import SentenceTransformer
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
        "siapa namamu?": "Saya adalah chatbot berbasis BERT.",
        "apa kabar?": "Saya baik, terima kasih! Bagaimana denganmu?",
        "terima kasih": "Sama-sama! Senang bisa membantu."
    }

# Load model BERT
model = SentenceTransformer("all-mpnet-base-v2")

# Encode semua pertanyaan di database
questions = list(conversations.keys())
question_embeddings = model.encode(questions)

def chatbot_response(user_input):
    """Mencari jawaban terbaik menggunakan cosine similarity"""
    global question_embeddings    
    user_embedding = model.encode([user_input])
    scores = cosine_similarity(user_embedding, question_embeddings)[0]
    
    best_match_idx = np.argmax(scores)
    best_score = scores[best_match_idx]

    # Jika kemiripan cukup tinggi, berikan jawaban
    THRESHOLD = 0.7
    if best_score >= THRESHOLD:
        return conversations[questions[best_match_idx]]

    console.print("\n[bold red]Bot:[/] Saya belum tahu jawabannya. Apa jawaban yang benar?")
    new_response = input("You (jawaban): ")

    # Simpan pertanyaan baru ke database
    conversations[user_input] = new_response
    with open(DB_FILE, "w") as f:
        json.dump(conversations, f, indent=4)

    # Update embeddings
    questions.append(user_input)
    question_embeddings = model.encode(questions)

    return "Terima kasih! Saya akan mengingat ini."

# Jalankan chatbot
console.print("[bold green]Chatbot siap digunakan! Ketik 'exit' untuk keluar.[/]")
while True:
    user_input = input("\nYou: ")
    if user_input.lower() == "exit":
        break
    console.print(f"[bold blue]Bot:[/] {chatbot_response(user_input)}")

