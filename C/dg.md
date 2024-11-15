```mermaid
classDiagram
    class ATM
    {
        -int BankSerial
        -int Cash[4]
        -bool Bilingual
        -bool MultiBankSupport

    }
    class Bank
    {
        -string BankName
        -
    }
    class Account
    {   
        -int BankSerial
        -long int Account Number
        -int Password
    }
'''