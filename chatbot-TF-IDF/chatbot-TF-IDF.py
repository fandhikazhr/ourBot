import random
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity

# Dataset percakapan
conversations = {
    "halo": "Hai! Ada yang bisa saya bantu?",
    "siapa namamu?": "Saya adalah chatbot sederhana.",
    "apa kabar?": "Saya baik, terima kasih! Bagaimana denganmu?",
    "apa yang bisa kamu lakukan?": "Saya bisa berbicara denganmu dan menjawab pertanyaan sederhana.",
    "terima kasih": "Sama-sama! Senang bisa membantu."
}

# Buat TF-IDF Vectorizer
vectorizer = TfidfVectorizer()
X = vectorizer.fit_transform(conversations.keys())

def chatbot_response(user_input):
    user_vec = vectorizer.transform([user_input])
    similarities = cosine_similarity(user_vec, X)
    best_match = similarities.argmax()
    
    if similarities[0, best_match] > 0.3:  # Ambang batas kecocokan
        return list(conversations.values())[best_match]
    else:
        return random.choice(["Maaf, saya tidak mengerti.", "Bisa ulangi?", "Saya masih belajar nih!"])

# Jalankan chatbot
while True:
    user_input = input("You: ")
    if user_input.lower() == "exit":
        print("Bot: Sampai jumpa!")
        break
    print("Bot:", chatbot_response(user_input))

