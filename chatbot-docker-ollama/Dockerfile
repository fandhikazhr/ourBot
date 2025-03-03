# Gunakan image dasar dari Ollama
FROM ollama/ollama

# Install dependensi tambahan
RUN apt update && apt install -y python3 python3-pip

# Copy file chatbot ke dalam container
COPY chatbot.py /app/chatbot.py

# Pindah ke direktori /app
WORKDIR /app

# Install dependensi Python
RUN pip install requests

# Jalankan API Ollama dan unduh model sebelum menjalankan chatbot
CMD ollama serve & sleep 5 && ollama pull mistral && python3 chatbot.py

