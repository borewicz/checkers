# checkers

### Co to za badziew?
Ten projekt powstał z myślą o zaliczeniu jakże cudownego przedmiotu, jakim są Sieci Komputerowe 2.

### Czym różnią się od zwykłych szachów?
Niczym. Poza tym że paru ludzi ma jeden kolor i się głosuje na ruch. Nic odkrywczego.

### Wymagania
Serwer wymaga boosta, a klient - biblioteki Qt.

### Kompilacja
Ponieważ projekt pisały dwie osoby, każdą część projektu kompiluje siię  zupełnie inny sposób. 

##### Serwer
Ponieważ Pawlok używał ułomnego Eclipse'a, wynikowe Makefiles miały niewiele wspólnego z prawdziwymi i nie kompilowały się nigdzie poza komputerem Pawloka. Na szczęście od czego jest cmake?

```
$ cd checkers-server
$ cmake .
$ make
```

##### Klient

Tutaj sprawa jest prostsza - do Qt SDK dostajemy qmake'a:

```
$ cd checkers-client
$ qmake checkers-client.pro
$ make
```

##### API

Z myślą dla tych, którzy chcieliby zrobić własny, mniej durny klient, serwer udostępnia swego rodzaju API. Są to JSONy, przez są one ładne i przyjemne.

### Logowanie
```
{
	"request" : "connect",
	"nick" : "nick"
}
```
Jak to zrobimy, to serwer zwróci nam kolor:
```
{ 
	"status" : "ok", 
	"color" : "white" # "black"
}
```
Przy statusie innym niż OK nie będzie koloru. Logiczne.

A żeby się wylogować:

```
{
	"request" : "disconnect"
}
```

### Wiadomości

Wysyłamy tak...

```
{
	"request" : "message",
	"message" : "raz dwa trzy"
}
```
a odbierame tak:

```
{
	"request" : "message",
	"timestamp" : "213702042005", # tak bardzo into przyszłość
	"nick" : "masterczulki",
	"message" : "lecz sie kamil, lecz sie"
}
```

### Plansza

Damki oznacza się wielką literą. Owszem, wygląda to słabo, ale dalej będzie tylko gorzej.

```
{
   "board" : [
      [ "_", "b", "_", "b", "_", "b", "_", "b" ],
      [ "b", "_", "b", "_", "b", "_", "b", "_" ],
      [ "_", "b", "_", "b", "_", "b", "_", "b" ],
      [ "_", "_", "_", "_", "_", "_", "_", "_" ],
      [ "_", "_", "_", "_", "_", "_", "_", "_" ],
      [ "w", "_", "w", "_", "w", "_", "w", "_" ],
      [ "_", "w", "_", "w", "_", "w", "_", "w" ],
      [ "w", "_", "w", "_", "w", "_", "w", "_" ]
   ],
   "current color" : "white",
   "request" : "board",
   "time" : 1447975142
}
```

### Wysyłanie ruchu

Ten request to jest jakaś porażka, zrobiona chyba wyłącznie po to, aby piszącemu serwer było łatwiej i przyjemniej, natomiast typ od klienta musiał się tak z tym bawić że nie mógł w spokoju polurkować. 

Mianowicie: 
 - w *movement* przesyłamy kolejno wartości X1, Y1, X2, Y2 (dlatego też w kliencie musimy dla koloru przeciwnego przeliczać od nowa iksy i igreki, bo serwer jest głupi i nie rozróżnia)
 - jeżeli nie robimy już więcej ruchów (a wbrew pozorom się da), to wypełniamy resztę tablicy *-1*
 - *time* to timestamp + czas tury, to jest jednocześnie numer planszy dla klienta

```
{
	"request" : "movement",
	"time" : "123123 timestamp + czas tury, (to co odebrane razem z planszą"
	"movement" : [0,0,1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1]
}
```

##### Koniec gry

Jak już gra się skończy, to serwer wyśle nam to:
```
{
	"request" : "game_over",	
	"winner" : "white"  # lub "black", wiadomka
}
```
##### Statusy

Na powyższe requesty serwer zazwyczaj będzie nas zasypywał przeróżnymi statusami. Mają one format:
```
{ 
	"status" : "tu jakiś status",
	"cośtam" : "cośtam2" # tu jakieś dodatkowe info
}
```
Dostępne statusy:
 - *ok* - nic nie działa
 - *not available* - nick zajęty
 - *already connected* - jesteś już połączonyśmieszku, 13 wstrzałów w tył głowy czeka
 - *not connected* - jesteś niepołączony i nic nie zrobisz
 - *wrong move* - wysyłasz zły ruch
 - *request error* - coś się zepsuło i nie było mnie słychać

### Rozwój
Chcesz pomóc? To spadaj, najwyżej zrób forka i elo, nie chcemy cię więcej widzieć.


### Licencja
Tbw na licencję.`
