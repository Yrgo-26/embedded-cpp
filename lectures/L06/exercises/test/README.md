# L06 Testsvit

Enhetstester för övningsset 4 *Timer Class* i kursboken, §2.4 *Exercises*, byggda på ramverket
[QAcademy Test](https://github.com/qrtech-academy/test-framework), som ligger utcheckat som
submodulen `libs/test`. Kör `git submodule update --init` en gång om den katalogen är tom.

```bash
make                    # Bygg och kör sviten mot din kod i ../
make SOLUTIONS=1        # Samma tester, mot ../../appendix/solutions
make clean              # Ta bort testbinären.
```

`make test` i repots rot kör denna svit och samtliga andra lektioners.

> **Du ska inte skriva några tester i denna kurs.** Testsviten är given och färdig: du skriver din
> lösning på övningarna och kör `make test` för att se om den gör vad övningen ber om. Det här
> dokumentet beskriver vad sviten kontrollerar, så att ett testresultat går att tolka - det är inte
> en uppgift.
>
> Att själv skriva tester kommer i kursen **hårdvarunära testning**. Ordningen är avsiktlig: här får
> du se vad en testsvit är bra för, innan du skriver din första.


---

## Vad som körs, och när

| Binär | Byggs när | Testar |
|---|---|---|
| `exercise1` | `exercise1/include/driver/timer.hpp` och `exercise1/source/driver/timer.cpp` finns | `driver::Timer`, och programmet när `source/main.cpp` finns |

Så länge filerna inte finns rapporteras övningen som `SKIP`, tillsammans med den sökväg sviten väntar
på. Denna lektion har ingen `language`-binär: de påståenden om klasser som sviterna kontrollerar
tillhör L05, vars bilagor introducerar dem.

---

## Vad testerna kontrollerar

**Deklarationerna, inte bara beteendet.** Konstruktorn ska vara `explicit` och `noexcept`, klassen
`final`, frågemetoderna `const`, `noexcept` och `[[nodiscard]]`, och default-konstruktorn samt
samtliga kopierings- och flyttoperationer raderade. Var och en är synlig för kompilatorn, så testerna
frågar den med type traits och `noexcept(...)`.

**Utskriften, exakt.** Testet jämför det programmet skriver ut med exempelutdatan, tecken för tecken,
och rapporterar den första rad som skiljer sig. Det inkluderar destruktorn:
`Stopping timer before deletion!` skrivs ut av en timer som är igång, och får inte skrivas ut av en
stoppad.

**De gränsfall som specifikationen namnger.** En timer som skapas med timeouten 0 är inte initierad,
och `start()` samt `toggle()` ska lämna den stoppad. En timer som är igång löper ut på exakt sitt
timeout:te tick, och `hasTimedOut()` återställer räknaren, så att nästa timeout ligger en hel timeout
senare.
