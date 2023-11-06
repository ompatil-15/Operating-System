#!/bin/bash

ADDRESS_BOOK='address_book.txt'

create_addressbook() {
    touch "$ADDRESS_BOOK"
    printf "Address book %s created succesfully" "$ADDRESS_BOOK"
    
}

display_addressbook() {
    lines=$(cat $ADDRESS_BOOK | wc -l)
    cat "$ADDRESS_BOOK"
    printf "\nTotal Records: %s" "$lines"
}

insert_record() {

    printf "Enter Personal Information\n\n"
   
    while true; do 
        read -rp "Full Name: " name
        if [ -z "$name" ] || [[ "$name" =~ [0-9] ]]; then
            printf "[*] - Enter a valid Name\n"
        else 
            break
        fi
    done

    while true; do 
        read -rp "Address: " address
        if [ -z "$address" ]; then
            printf "[*] - Enter a valid Address\n"
        else 
            break
        fi
    done

    while true; do 
        read -rp "Phone: " phone
        if [ -z "$phone" ] || ! [[ "$phone" =~ ^[0-9]{10}$ ]]; then
            printf "[*] - Enter a valid Phone Number\n"
        else 
            break
        fi
    done

    while true; do 
        read -rp "Email: " email
        if [ -z "$email" ] || ! [[ "$email" =~ ^[a-zA-Z0-9._]+@[A-Za-z]+\.[A-Za-z]{2,4}$ ]]; then
            printf "[*] - Enter a valid Email\n"
        else 
            break
        fi
    done

       
    record="$name\t\t\t$address\t\t$phone\t\t$email"
    echo -e "$record" >> "$ADDRESS_BOOK"
    printf "\nInformation succesfully stored in address book"

}

delete_record() {
    read -r -p "Enter name to delete: " name

    if [ -z "$name" ]; then
        echo "[*] - Enter a valid name"
    else
        if grep -i "$name" "$ADDRESS_BOOK" > /dev/null; then
            grep -iv "$name" "$ADDRESS_BOOK" > "$ADDRESS_BOOK.tmp"
            mv "$ADDRESS_BOOK.tmp" "$ADDRESS_BOOK"
            echo "Record succesfully deleted"
        else
            echo "Record not found"
        fi
    fi
}

update_record() {
    read -r -p "Enter name of record to update: " name

    if [ -z "$name" ]; then
        echo "[*] - Enter a valid name"
    else    
        if grep -i "$name" "$ADDRESS_BOOK" > /dev/null; then
            echo "Enter  new personal information for $name"
            while true; do 
                read -rp "Full Name: " new_name
                if [ -z "$name" ] || [[ "$new_name" =~ [0-9] ]]; then
                    printf "[*] - Enter a valid Name\n"
                else 
                    break
                fi
            done

            while true; do 
                read -rp "Address: " new_address
                if [ -z "$new_address" ]; then
                    printf "[*] - Enter a valid Address\n"
                else 
                    break
                fi
            done

            while true; do 
                read -rp "Phone: " new_phone
                if [ -z "$new_phone" ] || ! [[ "$new_phone" =~ ^[0-9]{10}$ ]]; then
                    printf "[*] - Enter a valid Phone Number\n"
                else 
                    break
                fi
            done
            
            while true; do 
                read -rp "Email: " new_email
                if [ -z "$new_email" ] || ! [[ "$new_email" =~ ^[a-zA-Z0-9._]+@[A-Za-z]+\.[A-Za-z]{2,4}$ ]]; then
                    printf "[*] - Enter a valid Email\n"
                else 
                    break
                fi
            done    
        
            sed -i -e "/$name/ s/.*/$new_name\t\t\t$new_address\t\t$new_phone\t\t$new_email/" "$ADDRESS_BOOK"
            echo "Record succesfully updated"
        else
            echo "Record not found"
        fi
    fi
}

while true; do
    printf "\n\nAddress Book Menu\n
1 - Create Address Book
2 - Display Address Book
3 - Insert a Record
4 - Delete a Record
5 - Update a Record
6 - Exit"

    printf "\n\n"
    read -rp "Enter menu choice: " choice
    printf "\n"
    
    case "$choice" in 
        "1") create_addressbook;;
        "2") display_addressbook;;
        "3") insert_record;;
        "4") delete_record;;
        "5") update_record;;
    esac
done