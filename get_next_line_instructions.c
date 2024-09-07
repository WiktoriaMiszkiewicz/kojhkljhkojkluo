/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaniec <wdaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:12:44 by wdaniec           #+#    #+#             */
/*   Updated: 2024/07/20 13:17:34 by wdaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"	


// Sprawdzanie, czy backup jest pusty.
// Przypisanie backup do tymczasowej zmiennej.
// Łączenie przeczytanych danych z poprzednimi danymi.
// Zwolnienie starej pamięci.
// Sprawdzanie, czy znaleźliśmy znak nowej linii.
static char     *function_name(int fd, char *buf, char *backup)
{
    int     read_line;
    char    *char_temp;

    read_line = 1;
    while (read_line != '\0')
    {
        read_line = read(fd, buf, BUFFER_SIZE);
        if (read_line == -1)
            return (0);
        else if (read_line == 0)
            break;
        buf[read_line] = '\0';
        if (!backup)                        // jesli backup pusty to stworzmy pusty string bo to pierwsza iteracja
            backup = ft_strdup("");
        char_temp = backup;                 // przypisz to do zmiennej tymczasowej
        backup = ft_strjoin(char_temp, buf); //łączy char temp z bufem i przypisuje do backup
        free(char_temp);                    // zwalnia pamiec zajmowana chartemp
        char_temp = NULL;               // zeby zapobiec przypadkowemu uzyciu zwolnionej pamieci
        if (ft_strchr (buf, '\n'))      // czy w buf jest znak nowej linii, bo jesli znak jest w nowej linii to znczy ze przeczytalismy cala linie i mozemy przerwac petle
            break;
    }
    return (backup);
}

statich char    *extract(char *line)
{
    size_t count;
    char *backup;

    count = 0;
    while (line[count] != '\n' && line[count] != '\0')  // liczny znaki az do napotakania znaku nowej linii lub jej konca
        count++;
    if (line[count] == '\0' || line[1] == '\0') // jesli osiagnieto koniec ciagu, nie ma nic do wyodrebnienia wiec funkcja zwraca null
        return (0);
    backup = ft_substr(line, count +1, ft_strlen(line) - count); // tworzy nowy ciag znakow backup , ktory zawiera po znaku nowej linii,
    if(*backup == '\0') // czy backup jest pusty, jesli tak to zwalnia pamiec
    {
        free(backup);
        backup = NULL;
    }
    line[count +1] = '\0'; // dodaje znak konca ciagu '\0' po znaku nowej linii w line, aby line zawieral tylko jedna linia tekstu od poczatku nowej linii
    return (backup); //backup zawiera czesc tekstu po znaku nowej linii ktora bedziemy dalej przetwarzac
}

char    *get_next_line(int fd)
{
    char    *line;
    char    *buf;
    static char *backup;

    if(fd < 0 || BUFFER_SIZE <= 0) // sprawdza czy deskryptor jest poprawny(nieujemny) i czy jest >0, jesli ni sa spelnione to blad
        return (0);
    buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE +1)) //alokuje pamiec dla bufora + jeden dodatkowy bajt (bufo sluzy do temp przechowywania i odczytywania danych)
    if (!buf)
        return (0);
    line = function_name(fd, buf , backup); //wywoluje funkcje, ktora odcztuje dane z pliku o deksyptorze fd , zapisuje je do bufora buf i skleja z ewentualnymi danymi z backup a wynik przypisuje do line
    free(buf);                      // zwalnia pamiec przydzielona do bufora
    buf = NULL;
    if (!line)              // check czy dane odczytane, jesli puste to funckja zwrwaca null bo nie udalo sie odczytac danych
        return (NULL);
    backup = extract(line); //extact wyodrebnia reszte tekstu po znaku nowej linii z line i przypisuje do backup
    return (line); //zwrocenie odczytanej linii
}