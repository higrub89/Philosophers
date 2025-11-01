#!/bin/zsh

echo '\e[91m _____ _   _ _               _                   _____         _
|  _  | |_|_| |___ ___ ___ ___| |_ ___ ___ ___     |_   _|__ ___| |_ ___ ___
|   __|   | | | . |_ -| . | . |   | -_|  _|_ -|       | || -_|_ -|  _| -_|  _|
|__|  |_|_|_|_|___|___|___|  _|_|_|___|_| |___|       |_||___|___|_| |___|_|
                          |_|                                            \e[0m\n'

# --- Argumento Simplificado ---
if [ "$#" -ne 1 ]; then
    echo "Usage: ./tester.sh <Project Folder>"
    echo "\tEjemplo: ./tester.sh .."
    exit
fi

echo "\e[92m[+] Given Folder: $1\e[0m\n"
echo "\e[94m[+] In Case of a failed test, please check ./errors_log file for more information\e[0m\n"

# --- Función de Log ---
error_log ()
{
    echo "[$1-$2]: $3" >> ./errors_log
}

# --- Pruebas del Tester Original (1-5) ---

test_one ()
{
    ("$2/$1/$1" 4 310 200 100 > "./log_$1")&
    sleep 5
    pkill $1
    output=$(grep died -m 1 "./log_$1" | awk '{print $NF}')
    if [ "$output" = "died" ];then
        echo "\e[92m[+] Test #1 (Must Die) Succeeded !\e[0m"
    else
        echo "\e[91m[+] Test #1 (Must Die) Failed !\e[0m"
        error_log $1 "Test #1" "Given 4 310 200 100 arguments to $1, a philosopher should die !"
    fi
    rm -rf "./log_$1"
}

test_two ()
{
    echo "\e[94m[+] Test #2 (No Death): Executing for 60s, please wait...\e[0m"
    ("$2/$1/$1" 4 410 200 200 > /dev/null)&
    i=1
    error=0
    while [ $i -lt 60 ];do # 60 segundos (en vez de 180)
        printf "\r[%d...]" $i
        pgrep $1 > /dev/null
        if [ "$?" -ne 0 ];then
            echo "\r\e[91m[+] Test #2 (No Death) Failed\e[0m"
            error_log $1 "Test #2" "Given 4 410 200 200 arguments to $1, no philosopher should die !"
            error=1
            break
        fi
        sleep 1
        i=$(( $i + 1 ))
    done
    sleep 1
    if [ $error -eq 0 ];then
        pkill $1
        echo "\r\e[92m[+] Test #2 (No Death) Succeeded!\e[0m"
    fi
}

test_three ()
{
    echo "\e[94m[+] Test #3 (Odd N): Executing for 60s, please wait...\e[0m"
    ("$2/$1/$1" 5 800 200 200 > /dev/null)&
    i=1
    error=0
    while [ $i -lt 60 ];do # 60 segundos
        printf "\r[%d...]" $i
        pgrep $1 > /dev/null
        if [ "$?" -ne 0 ];then
            echo "\r\e[91m[+] Test #3 (Odd N) Failed\e[0m"
            error_log $1 "Test #3" "Given 5 800 200 200 arguments to $1, no philosopher should die !"
            error=1
            break
        fi
        sleep 1
        i=$(( $i + 1 ))
    done
    sleep 1
    if [ $error -eq 0 ];then
        pkill $1
        echo "\r\e[92m[+] Test #3 (Odd N) Succeeded!\e[0m"
    fi
}

test_four ()
{
    ("$2/$1/$1" 4 410 200 200 $3 > "./log_$1")&
    sleep 10
    pgrep $1 > /dev/null
    if [ "$?" -eq 1 ];then # $? = 1 significa que NO está corriendo (paró solo, bien)
        lines=$(grep eating "./log_$1" | wc -l)
        if [ $lines -ge $4 ];then
            echo "\t\e[92m[+] Test #4-$5 (Meals) Succeeded\e[0m"
        else
            echo "\t\e[91m[+] Test #4-$5 (Meals) Failed\e[0m"
            error_log $1 "Test #4" "Program stopped, but not enough meals were eaten!"
        fi
    else # $? = 0 significa que SIGUE corriendo (mal)
        echo "\t\e[91m[+] Test #4-$5 (Meals) Failed\e[0m"
        error_log $1 "Test #4" "Given 'meals' argument, program did not stop!"
        pkill $1
    fi
    rm -rf "./log_$1"
}

test_five ()
{
    echo "\e[94m[+] Test #5 (Death Time): on progress, please wait...\e[0m"
    i=1
    t=0
    error=0
    while [ $i -le 10 ];do
        ("$2/$1/$1" 2 60 60 60 > "./log_$1")&
        sleep 2
        pgrep $1 > /dev/null
        if [ "$?" -eq 1 ];then
            printf "\r[%d/10]" $i
            tmp=$(grep died -m 1 "./log_$1" | awk '{print $1}' | sed 's/[^0-9]*//g')
            if [ $i -gt 1 ];then
                x=$(expr $tmp - $t)
                x=${x#-}
                if [ $x -gt 10 ];then
                    printf "\r\e[91m[+] Test #5 (Death Time) Failed\e[0m\n"
                    error_log $1 "Test #5" "Time difference of death is bigger than 10ms !"
                    error=1
                    break
                fi
            else
                t=$tmp
            fi
        else
            printf "\r\e[91m[+] Test #5 (Death Time) Failed\e[0m\n"
            error_log $1 "Test #5" "A philosopher should die !"
            pkill $1
            break
        fi
        i=$(( $i + 1 ))
    done
    if [ $error -eq 0 ];then
        echo "\r\e[92m[+] Test #5 (Death Time) Succeeded\e[0m"
    fi
}

# --- NUESTRAS NUEVAS PRUEBAS (6 y 7) ---

test_six ()
{
    echo "\e[94m[+] Test #6 (1-Philo): Checking 1 philosopher case...\e[0m"
    ("$2/$1/$1" 1 400 200 200 > "./log_$1")&
    sleep 2 # Dar 2 segundos para morir (debería morir a los 400ms)
    pgrep $1 > /dev/null
    if [ "$?" -eq 1 ];then # $? = 1 significa que NO está corriendo (paró solo, bien)
        output=$(grep died -m 1 "./log_$1" | awk '{print $NF}')
        if [ "$output" = "died" ];then
            echo "\e[92m[+] Test #6 (1-Philo) Succeeded !\e[0m"
        else
            echo "\e[91m[+] Test #6 (1-Philo) Failed !\e[0m"
            error_log $1 "Test #6" "Program stopped, but did not print 'died'!"
        fi
    else # $? = 0 significa que SIGUE corriendo (mal, deadlock)
        echo "\e[91m[+] Test #6 (1-Philo) Failed !\e[0m"
        error_log $1 "Test #6" "Given 1 400 200 200, program did not stop (deadlock)!"
        pkill $1
    fi
    rm -rf "./log_$1"
}

test_seven ()
{
    echo "\e[94m[+] Test #7 (200-Philo Stress): Running for 30s, please wait...\e[0m"
    ("$2/$1/$1" 200 800 200 200 > /dev/null)&
    i=1
    error=0
    while [ $i -lt 30 ];do # Loop por 30 segundos
        printf "\r[%d...]" $i
        pgrep $1 > /dev/null
        if [ "$?" -ne 0 ];then # $? != 0 significa que no está corriendo (alguien murió)
            echo "\r\e[91m[+] Test #7 (200-Philo Stress) Failed\e[0m"
            error_log $1 "Test #7" "Given 200 800 200 200, a philosopher died!"
            error=1
            break
        fi
        sleep 1
        i=$(( $i + 1 ))
    done
    sleep 1
    if [ $error -eq 0 ];then
        pkill $1
        echo "\r\e[92m[+] Test #7 (200-Philo Stress) Succeeded\e[0m"
    fi
}


# --- Bloque de Ejecución (Solo Philo) ---

echo "[============[Testing philo]==============]"

target="philo"
# Asumimos que la carpeta es $1/philo
make -C "$1/philo" > /dev/null

if [ "$?" -ne 0 ];then
    echo "\n[+] There's a problem while compiling $target, please recheck your inputs"
    exit
fi

test_one $target $1
test_two $target $1
test_three $target $1

echo "\e[94m[+] Test #4 (Meals) on progress, please wait...\e[0m"
test_four $target $1 7 28 1
test_four $target $1 10 40 2
test_four $target $1 12 48 3
test_four $target $1 15 60 4

test_five $target $1

# --- Llamadas a las nuevas pruebas ---
test_six $target $1
test_seven $target $1

rm -rf "./log_$target"
rm -rf ./errors_log # Limpiar log de errores si todo fue bien

echo "\n[+] Testing finished !"
