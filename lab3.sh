#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Использование: $0 <файл>"
    exit 1
fi

filename=$1

add_expense() {
    echo "Добавить новый расход:"
    read -p "Дата (ГГГГ-ММ-ДД): " date
    read -p "Категория: " category
    read -p "Сумма: " amount
    read -p "Описание: " description
    
    echo "$date|$category|$amount|$description" >> "$filename"
    echo "Запись добавлена!"
}

view_expenses() {
    if [ ! -f "$filename" ]; then
        echo "Файл не существует"
        return
    fi
    
    echo "Список расходов:"
    echo "----------------"
    cat "$filename" | while IFS='|' read date category amount description; do
        echo "Дата: $date, Категория: $category, Сумма: $amount, Описание: $description"
    done
}

while true; do
    echo ""
    echo "1. Добавить расход"
    echo "2. Просмотреть расходы"
    echo "3. Выйти"
    read -p "Выберите действие: " choice

    case $choice in
        1) add_expense ;;
        2) view_expenses ;;
        3) exit 0 ;;
        *) echo "Неверный выбор" ;;
    esac
done
