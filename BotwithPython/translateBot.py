import telebot
from telebot import types
from datetime import datetime
from googletrans import Translator, constants
from pprint import pprint

api = 'YOUR TOKEN BOT'
bot = telebot.TeleBot(api)

translator = Translator()

@bot.message_handler(commands=['start'])
def selamat_datang(message):
    #bot.reply_to(message, 'Selamat Datang!')
    markup = types.ReplyKeyboardMarkup(row_width=1)
    btn1 = types.KeyboardButton('/help')
    btn2 = types.KeyboardButton('/about')
    btn3 = types.KeyboardButton('/info')
    markup.add(btn1, btn2, btn3)
    chatid = message.chat.id
    bot.send_message(chatid, text='', reply_markup=markup)

@bot.message_handler(commands=['help'])
def tolong_saya(message):
    chatid = message.chat.id
    bot.send_message(chatid, '???')
    bot.send_message(chatid, '')

@bot.message_handler(commands=['about'])
def tentang_bot(message):
    chatid = message.chat.id
    bot.send_message(chatid, '')

@bot.message_handler(commands=['info'])
def tentang_bot(message):
    chatid = message.chat.id
    bot.send_message(chatid, '')

@bot.message_handler(content_types=['text'])
def transtoindo(message):
    translation = translator.translate(message.text, dest="id")
    srclangs = translator.detect(message.text)
    chatid = message.chat.id
    bot.send_message(chatid,text=''+srclangs.lng)
    bot.send_message(chatid, text=''+translation.txt)
    print(""+message.txt)
    print(""+srclangs.lng)
    print(""+translation.txt+"\n")

print('Running')
bot.polling()
