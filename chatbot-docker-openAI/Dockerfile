# Menggunakan image Python versi 3.9 (bisa diganti sesuai kebutuhan)
FROM python:3.9-slim

# Mengatur working directory di dalam container
WORKDIR /app

# Salin file requirements.txt ke dalam container
COPY requirements.txt .

# Install dependensi Python
RUN pip install --no-cache-dir -r requirements.txt

# Salin seluruh kode ke dalam container
COPY . .

# Jalankan chatbot
CMD ["python", "chatbot.py"]

