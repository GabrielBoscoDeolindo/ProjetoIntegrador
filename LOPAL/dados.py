import pandas as pd
import openpyxl
import smtplib
from email.mime.text import MIMEText

# Script do EMAIL
def send_email(subject, body, sender, recipients, password):
    msg = MIMEText(body)
    msg['Subject'] = subject
    msg['From'] = sender
    msg['To'] = ', '.join(recipients)
    with smtplib.SMTP_SSL('smtp.gmail.com', 465) as smtp_server:
       smtp_server.login(sender, password)
       smtp_server.sendmail(sender, recipients, msg.as_string())
    print("Mensagem enviada!")
    
# Calcula o estoque de cada dia em cada esteira
def CalculoEstoque(dias, esteira):
    estoque_cheio = 0
    estoque_medio = 0
    estoque_baixo = 0
    maquina_problema = 0
    for data, valor_esteira in zip(dias, esteira): #Uma esteira de cada vez
        if valor_esteira >= 3:
            estoque_cheio+=1 #Aumenta o valor de cada estoque cheio
        elif valor_esteira >= 2:
            estoque_medio+=1 #Aumenta o valor de cada estoque medio
        elif valor_esteira >= 1:
            estoque_baixo+=1 #Aumenta o valor de cada estoque baixo
        else:
            maquina_problema+=1 #Aumenta o valor de cada esteira problema
            
    data = { #Transforma os Dados em um dicionário
        "Estoque cheio": [estoque_cheio], 
        "Estoque médio": [estoque_medio], 
        "Estoque baixo": [estoque_baixo], 
        "Máquina com problema": [maquina_problema]
    }
    return pd.DataFrame(data) #Transforma esses dados em um DataFrame


# Lendo o arquivo CSV
arquivo = pd.read_csv("esteira.csv")

# Puxando os dados do CSV das tabelas que quero
dias = arquivo["Date"].values
estoque_esteira1 = arquivo["esteira1"].values
estoque_esteira2 = arquivo["esteira2"].values
estoque_esteira3 = arquivo["esteira3"].values

# Calculando os dados para cada esteira
df1 = CalculoEstoque(dias, estoque_esteira1)
df2 = CalculoEstoque(dias, estoque_esteira2)
df3 = CalculoEstoque(dias, estoque_esteira3)

# Combinando os DataFrames em um único df
df_combinado = pd.concat([df1, df2, df3], ignore_index=True)

# Escrevendo no excel 
df_combinado.to_excel("produtos.xlsx", index=False)

#Manda o Email
subject = "RELATÓRIO - ESTOQUE"
body = f"""
RELATÓRIO - ESTOQUE:
{df_combinado}
"""
sender = "gabibosco01@gmail.com"
recipients = ["gabibosco01@gmail.com"]
password = "PLACEHOLDER"
send_email(subject, body, sender, recipients, password)



