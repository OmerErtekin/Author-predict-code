#ifndef _TYPES_H_
#define _TYPES_H_

#define MAX_AUTHORS 16

struct features {
    char *author;                   // yazar adi
    double avg_word_length;         // ortalama kelime uzunlugu
    double ttr;                     // TTR
    double hapax;                   // Hapax Legomana Orani
    double avg_word_per_sentence;   // Cumle basina ortalama kelime orani
    double complexity;              // Cumle basina ortalama alt-cumle orani
};

#endif
