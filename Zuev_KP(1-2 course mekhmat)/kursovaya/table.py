import sqlite3

try:
    sqlite_connection = sqlite3.connect('Game.db')
    cursor = sqlite_connection.cursor()
    
    sqlite_create_table0 = '''CREATE TABLE Trick (
                                trick_k INTEGER,
                                game_k INTEGER,
                                move INTEGER,
                                firsthand INTEGER,
                                card1 INTEGER,
                                card2 INTEGER,
                                card3 INTEGER,
                                winner INTEGER);'''

    cursor.execute(sqlite_create_table0)
    sqlite_connection.commit()

    sqlite_create_table1 = '''CREATE TABLE Hand (
                                k INTEGER,
                                card INTEGER,
                                game_k INTEGER);'''
    
    cursor.execute(sqlite_create_table1)
    sqlite_connection.commit()

    cursor.close()
    
except sqlite3.Error as error:
    print("Ошибка при подключении к sqlite", error)
finally:
    if (sqlite_connection):
        sqlite_connection.close()
        