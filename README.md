# Sztuczne życie (Artificial Life)


## Wymagania
Aby zbudować projekt celem jego uruchomienia wymagane są następujące zależności zewnętrzne:
- [**SDL2**](https://github.com/libsdl-org/SDL)
- [**gtest**](https://github.com/google/googletest) (tylko testy jednostkowe)

Do budowania plików projektów wykorzystany został program [**CMake**](https://cmake.org/).

## Budowanie
### Ogólne
Dostępne są następujące opcje budowania projektu CMake wraz z ich wartościami domyślnymi:
- **BUILD_TEST=ON**
- **BUILD_DEPENDENCIES=OFF**

W plikach projektu zawarte zostały pliki źródłowe podanych wyżej zależności zewnętrznych. Szczególnie ważne w tym kontekście jest opcja **BUILD_DEPENDENCIES** - jeśli jest ona ustawiona na **OFF**, wykorzystane zostaną zainstalowane już biblioteki w systemie, w przeciwnym przypadku, gdy jest ona ustawiona na **ON**, rozpocznie się proces budowania plików źródłowych z zamieszczonych źródeł i zostaną one wykorzystane przez projekt.
### Linux
W przypadku systemów operacyjnych opartych na jądrze Linux zalecane jest wykorzystanie *menadżerów pakietów* celem zainstalowania zależności zewnętrznych.

W przypadku dystrybucji wykorzystujących **apt** należy zainstalować CMake oraz pakiety niezbędne do budowania projektów w następujący sposób:
```
apt install cmake
apt install build-essential
```
Ponadto, do projektu dodano skrypty upraszczające proces budowania i uruchamiania:
- **build.sh** (buduje cały projekt z domyślnymi ustawieniami - **zalecane**)
- **run.sh** (uruchamia wynik kompilacji)
- **runtests.sh** (uruchamia testy jednostkowe)
- **apt-install/gtest-install.sh** (instaluje gtest z repozytorium)
- **apt-install/sdl2-install.sh** (instaluje SDL2 z repozytorium)
- **apt-install/sdl2-ttf-install.sh** (instaluje SDL2 ttf z repozytorium)

### Windows
W przypadku systemów Windows zalecane jest wykorzystanie zawartych w katalogu **third party** źródeł, a następnie dołączeniu ich do projektu. W tym celu należy uruchomić następujące polecenia:
```
mkdir build
cd build
cmake .. -DBUILD_DEPENDENCIES=ON
cd ..
```

## Autorzy
Autorami projektu są **Mateusz Jurczak** oraz **Julia Parobczy**.

## Licencja
Projekt **Sztuczne Życie** rozpowszechaniany jest na zasadach licencji wolnego oprogramowania **GNU GPLv3.0**.
