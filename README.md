# Gestion d'Établissement

## Introduction

Ce projet de gestion d'établissement en C++, encadré par Ennaji Fatima Zohra, permet aux professeurs et aux étudiants de gérer les informations académiques liées aux cours, aux enseignants, aux étudiants et aux notes.

## Fonctionnalités

- Gestion des informations académiques
- Connexion sécurisée pour étudiants, professeurs et directeurs
- Affichage et mise à jour des notes

## Bibliothèques Utilisées

- `<cstdlib>` : Gestion de la mémoire dynamique
- `<cstring>` : Manipulation de chaînes de caractères
- `<vector>` : Tableaux dynamiques
- `<iostream>` : Entrée/sortie standard
- `<sqlite3.h>` : Gestion de la base de données SQLite

## Structure du Projet

### Espaces Utilisateurs

- **Étudiant** : Accès aux notes personnelles.
- **Professeur** : Accès et mise à jour des notes des étudiants.
- **Directeur** : Consultation et modification des notes de tous les étudiants.

### Fonctions Principales

- `recherche_mail_password` : Recherche un utilisateur.
- `updateNotes` : Met à jour les notes d'un étudiant.
- `login_page` : Gère le processus de connexion.

## Connexion à la Base de Données

- `sqlite3_open` : Ouvre la base de données.
- `sqlite3_prepare_v2` : Compile une requête SQL.
- `sqlite3_step` : Exécute l'instruction SQL.
- `sqlite3_finalize` : Libère les ressources.

## Conclusion

Ce projet démontre l'efficacité de C++ et SQLite pour la gestion des données académiques dans un environnement éducatif. L'implémentation actuelle offre une base solide pour une gestion transparente et sécurisée des informations académiques. Avec des améliorations futures, ce système pourrait être étendu pour inclure des fonctionnalités supplémentaires et s'adapter aux besoins évolutifs des établissements éducatifs.

