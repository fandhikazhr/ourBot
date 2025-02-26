import openai
import os
from rich.console import Console

# Inisialisasi konsol Rich untuk tampilan di terminal
console = Console()

# Ambil API Key dari variabel lingkungan
API_KEY = os.getenv("OPENAI_API_KEY")
if not API_KEY:
    console.print("[bold red]Error:[/bold red] API key tidak ditemukan. Silakan set environment variable OPENAI_API_KEY.")
    exit(1)

# Buat objek klien OpenAI
client = openai.OpenAI(api_key=API_KEY)

def chatbot():
    console.print("[bold green]ChatGPT Terminal Chatbot[/bold green] (ketik 'exit' untuk keluar)")
    chat_history = []  # Menyimpan riwayat percakapan

    while True:
        user_input = console.input("[bold cyan]Kamu:[/bold cyan] ")
        if user_input.lower() in ["exit", "keluar", "quit"]:
            console.print("[bold red]Chatbot ditutup.[/bold red]")
            break

        chat_history.append({"role": "user", "content": user_input})

        # Perbaikan pemanggilan API sesuai format OpenAI terbaru
        response = client.chat.completions.create(
            model="gpt-3.5-turbo",  # atau "gpt-3.5-turbo" jika ingin lebih hemat
            messages=chat_history
        )
        bot_response = response.choices[0].message.content
        chat_history.append({"role": "assistant", "content": bot_response})

        console.print(f"[bold yellow]ChatGPT:[/bold yellow] {bot_response}")

if __name__ == "__main__":
    chatbot()

