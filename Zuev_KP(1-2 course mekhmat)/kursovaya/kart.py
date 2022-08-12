import numpy as np
import random
import sqlite3

def insert_varible_into_trick(trick_k, game_k, move, firsthand, card1, card2, card3, winner):
    try:
        sqlite_connection = sqlite3.connect('Game.db')
        cursor = sqlite_connection.cursor()

        sqlite_insert_with_param = """INSERT INTO Trick
                              (trick_k, game_k, move, firsthand, card1, card2, card3, winner)
                              VALUES (?, ?, ?, ?, ?, ?, ?, ?);"""

        data = (trick_k, game_k, move, firsthand, card1, card2, card3, winner)
        cursor.execute(sqlite_insert_with_param, data)
        sqlite_connection.commit()

        cursor.close()

    except sqlite3.Error as error:
        print("Ошибка", error)
    finally:
        if sqlite_connection:
            sqlite_connection.close()
            
def read_sqlite_trick():
    try:
        sqlite_connection= sqlite3.connect('Game.db')
        cursor = sqlite_connection.cursor()
        
        if (cursor.fetchall() == None):
            return 0
        
        sqlite_select_query = """SELECT count(*) from Trick"""
        cursor.execute(sqlite_select_query)
        
        rows = cursor.fetchone()
        
        cursor.close()
        
        return rows

    except sqlite3.Error as error:
        print("Ошибка", error)
    finally:
        if (sqlite_connection):
            sqlite_connection.close()
            
def insert_varible_into_hand(k, card, game_k):
    try:
        sqlite_connection = sqlite3.connect('Game.db')
        cursor = sqlite_connection.cursor()

        sqlite_insert_with_param = """INSERT INTO Hand
                              (k, card, game_k)
                              VALUES (?, ?, ?);"""

        data = (k, card, game_k)
        cursor.execute(sqlite_insert_with_param, data)
        sqlite_connection.commit()

        cursor.close()

    except sqlite3.Error as error:
        print("Ошибка", error)
    finally:
        if sqlite_connection:
            sqlite_connection.close()
            
def read_sqlite_hand():
    try:
        sqlite_connection= sqlite3.connect('Game.db')
        cursor = sqlite_connection.cursor()
        
        if (cursor.fetchall() == None):
            return 0
        
        sqlite_select_query = """SELECT count(*) FROM hand"""
        cursor.execute(sqlite_select_query)
        
        (count,) = cursor.fetchone()
        
        cursor.close()
        
        return count

    except sqlite3.Error as error:
        print("Ошибка", error)
    finally:
        if (sqlite_connection):
            sqlite_connection.close()
            
class Deck():
    deck = [None] * 32
    def __init__(self):
        for i in range(1, 5):
            for j in range(7, 15):
                self.deck[(i - 1) * 8 + (j - 6) - 1] = Card(i, j)
    def get(self, i):
        try:
            answer = {
                11: "Валет",
                12: "Дама",
                13: "Король",
                14: "Туз",
            }[self.deck[i].Num]
        except:
            answer = str(self.deck[i].Num)
        answer += " "
        answer += {
            1: "червы",
            2: "бубны",
            3: "крести",
            4: "пики",
        }[self.deck[i].Mastb]
        return answer

class Card():
    def __init__(self, i, j):
        self.Mastb = i
        self.Num   = j








class Player():
    
    
    def Sdelaykhod(self, m):
        raise NotImplemented 
        
    def Poluchi(self, k, m):
        hand = [None] * 11
        for i in range(1+(k-1)*10, 11+(k-1)*10):
            hand[i-(k-1)*10] = m[i]
        for i in range(1, 11):
             for j in range(1, 33):
                 if (j == hand[i]):
                     self.deck[j] = 1
                 if (j != hand[i]) & (self.deck[j] != 1):
                     self.deck[j] = 0
        return self.deck

    def Recording(self):
        l = str(read_sqlite_hand())
        s = int    
        if (l == '0'):
            s = 0
            l = int(l)
        else:
            l = l[1:-1+len(l)-1]
            l = int(l)
            s = l
        for i in range(1, 33):
            if (self.deck[i] == 1):
                s = s+1
                insert_varible_into_hand(s, i, l/10+1)
                
                
                
                
                
#class crupie():
    #подключить игрока
    #нейросетевой обычный 
    #полочи 
    #разыграй (метод сделац ход 30 раз)
                
        
class RandomPlayer(Player): 
    def __init__(self, deck):
        self.deck = deck
    
    def Sdelaykhod(self, m):
        s = int
        s = 0
        p = int
        p = 0
        l = int
        l = 0
        i = int
        i = 0
        data = []
        for k in range(1, 33):
            if (self.deck[k] == 1):
                data.append(k)
                l = l+1
            if (mast(k) == m) and (self.deck[k] == 1):
                p = p+1
        if (p == 0) or (m == 0):
            i = random.randint(0, l-1)
            s = data[i]
            self.deck[data[i]] = 0
        else:
            while i >= 0:
                i = random.randint(0, l-1)
                if (mast(data[i]) == m):
                    s = data[i]
                    self.deck[data[i]] = 0
                    break
        return s
    
    def Poluchi(self, k, m):
        hand = [None] * 11
        for i in range(1+(k-1)*10, 11+(k-1)*10):
            hand[i-(k-1)*10] = m[i]
        for i in range(1, 11):
             for j in range(1, 33):
                 if (j == hand[i]):
                     self.deck[j] = 1
                 if (j != hand[i]) & (self.deck[j] != 1):
                     self.deck[j] = 0
        return self.deck
    
    def uznay(self):
        return 1
    
    def Recording(self):
        l = str(read_sqlite_hand())
        s = int    
        if (l == '0'):
            s = 0
            l = int(l)
        else:
            l = l[1:-1+len(l)-1]
            l = int(l)
            s = l
        for i in range(1, 33):
            if (self.deck[i] == 1):
                s = s+1
                insert_varible_into_hand(s, i, l/10+1)
                
    def Print(self):
        print(self.deck, '\n')





#"приватные" методы крупье
def sravnit1(a, b, c, s): #сравнивает карты 1
    if (mast(b) == mast(a)) & (mast(c) == mast(a)):
        if (a > b) & (a > c):
            s[1] = s[1]+1
            s[4] = 1
        if (b > a) & (b > c):
            s[2] = s[2]+1
            s[4] = 2
        if (c > a) & (c > b):
            s[3] = s[3]+1
            s[4] = 3
    if (mast(b) != mast(a)) & (mast(c) == mast(a)):
        if (a > c):
            s[1] = s[1]+1
            s[4] = 1
        else:
            s[3] = s[3]+1
            s[4] = 3
    if (mast(b) == mast(a)) & (mast(c) != mast(a)):
        if (a > b):
            s[1] = s[1]+1
            s[4] = 1
        else:
            s[2] = s[2]+1
            s[4] = 2 
    if (mast(b) != mast(a)) & (mast(c) != mast(a)):
        s[1] = s[1]+1
        s[4] = 1
    print('\n')
    return s

def sravnit2(a, b, c, s): #сравнивает карты 2
    if (mast(a) == mast(b)) & (mast(c) == mast(b)):
        if (a > b) & (a > c):
            s[1] = s[1]+1
            s[4] = 1
        if (b > a) & (b > c):
            s[2] = s[2]+1
            s[4] = 2
        if (c > a) & (c > b):
            s[3] = s[3]+1
            s[4] = 3
    if (mast(a) != mast(b)) & (mast(c) == mast(b)):
        if (b > c):
            s[2] = s[2]+1
            s[4] = 2
        else:
            s[3] = s[3]+1
            s[4] = 3
    if (mast(a) == mast(b)) & (mast(c) != mast(b)):
        if (a > b):
            s[1] = s[1]+1
            s[4] = 1
        else:
            s[2] = s[2]+1
            s[4] = 2
    if (mast(a) != mast(b)) & (mast(c) != mast(b)):
        s[2] = s[2]+1
        s[4] = 2
    print('\n')
    return s
    
def sravnit3(a, b, c, s): #сравнивает карты 3
    if (mast(b) == mast(c)) & (mast(a) == mast(c)):
        if (a > b) & (a > c):
            s[1] = s[1]+1
            s[4] = 1
        if (b > a) & (b > c):
            s[2] = s[2]+1
            s[4] = 2
        if (c > a) & (c > b):
            s[3] = s[3]+1
            s[4] = 3
    if (mast(b) != mast(c)) & (mast(a) == mast(c)):
        if (a > c):
            s[1] = s[1]+1
            s[4] = 1
        else:
            s[3] = s[3]+1
            s[4] = 3
    if (mast(b) == mast(c)) & (mast(a) != mast(c)):
        if (c > b):
            s[3] = s[3]+1
            s[4] = 3
        else:
            s[2] = s[2]+1
            s[4] = 2
    if (mast(b) != mast(c)) & (mast(a) != mast(c)):
        s[3] = s[3]+1
        s[4] = 3
    print('\n')
    return s
        
def mast(a):
    if (a>=1) & (a<=8):
        return(1)
    if (a>=9) & (a<=16):
        return(2)
    if (a>=17) & (a<=24):
        return(3)
    if (a>=25) & (a<=32):
        return(4)                        
    
if __name__ == '__main__':
    deck = Deck()
    otvet = [None] * 5
    for i in range(1, 4):
        otvet[i] = 0
    otvet[4] = random.randint(1, 3) #чей ход
    r = np.random.permutation(33)
    for i in range(0, 33):
        if (r[i] == 0):
            r[i] = r[0]
            r[0] = 0
            break
    
    neurons1 = [None] * 33
    neurons2 = [None] * 33
    neurons3 = [None] * 33
    
    player1 = Player(neurons1)
    player1.Poluchi(1, r)
    player1.Print()
    player1.Recording()
    
    player2 = Player(neurons2)
    player2.Poluchi(2, r)
    
    player3 = Player(neurons3)
    player3.Poluchi(3, r)
    
    # l = str(read_sqlite_trick())
    # s = 0    
    # if (l == '0'):
    #     s = 0
    #     l = int(l)
    # else:
    #     l = l[1:-1+len(l)-1]
    #     l = int(l)
    #     s = l
        
    for i in range(1, 11):
        if (otvet[4] == 1):
            k1 = player1.Sdelaykhod(0)
            k2 = player2.Sdelaykhod(mast(k1))
            k3 = player3.Sdelaykhod(mast(k1))
            print (k1, k2, k3, '*1 ходит 1-м') 
            otvet = sravnit1(k1, k2, k3, otvet)
            s = s+1
            insert_varible_into_trick(s, l/10+1, i, 1, k1, k2, k3, otvet[4])
            continue
        if (otvet[4] == 2):
            k2 = player2.Sdelaykhod(0) 
            k3 = player3.Sdelaykhod(mast(k2))
            k1 = player1.Sdelaykhod(mast(k2))
            print (k1, k2, k3, '*2 ходит 1-м') 
            otvet = sravnit2(k1, k2, k3, otvet)
            s = s+1
            insert_varible_into_trick(s, l/10+1, i, 2, k1, k2, k3, otvet[4])
            continue
        if (otvet[4] == 3):
            k3 = player3.Sdelaykhod(0)
            k1 = player1.Sdelaykhod(mast(k3))
            k2 = player2.Sdelaykhod(mast(k3))
            print (k1, k2, k3, '*3 ходит 1-м') 
            otvet = sravnit3(k1, k2, k3, otvet)
            s = s+1
            insert_varible_into_trick(s, l/10+1, i, 3, k1, k2, k3, otvet[4])
            continue
                 
    print('Ответ', otvet[1], otvet[2], otvet[3])