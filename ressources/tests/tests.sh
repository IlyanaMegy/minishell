#!/bin/bash

# Nom du fichier contenant les tests
TEST_FILE="draft.txt"

# Chemin vers le programme minishell
MINISHELL="../minishell"

# Fonction pour comparer la sortie de minishell avec la sortie attendue
compare_output() {
    local minishell_output=$1
    local expected_output=$2

    if [ "$minishell_output" = "$expected_output" ]; then
        echo "OK"
    else
        echo "Erreur: Sortie de minishell différente de la sortie attendue"
        echo "Minishell: $minishell_output"
        echo "Attendu  : $expected_output"
    fi
}

# Vérification si le fichier de tests existe
if [ ! -f "$TEST_FILE" ]; then
    echo "Fichier de tests '$TEST_FILE' introuvable."
    exit 1
fi

# Lecture ligne par ligne du fichier de tests
while IFS= read -r line; do
    # Ignorer les lignes vides ou les commentaires
    if [ -z "$line" ] || [[ "$line" == \#* ]]; then
        continue
    fi

    # Exécution de la commande avec minishell
    minishell_output=$(echo "$line" | $MINISHELL)

    # Exécution de la commande avec bash pour obtenir la sortie attendue
    expected_output=$(bash --posix -c "$line")

    echo "Commande: $line"

    # Comparaison des sorties
    compare_output "$minishell_output" "$expected_output"

    echo "==============================="
done < "$TEST_FILE"