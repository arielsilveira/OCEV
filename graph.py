from matplotlib import pyplot as pl

geracoes = []
solucoes_melhor = []
solucoes_media = []
solucoes_pior = []

with open('melhor.txt', 'r') as dataset:
	for line in dataset.readlines():
		line = line.strip()
		solucoes_melhor.append(float(line))

with open('media.txt', 'r') as dataset:
	for line in dataset.readlines():
		line = line.strip()
		solucoes_media.append(float(line))

with open('pior.txt', 'r') as dataset:
	for line in dataset.readlines():
		line = line.strip()
		solucoes_pior.append(float(line))

title = ''
with open('config.txt', 'r') as dataset:
	for line in dataset.readlines():
		line = line.strip()
		info, line = line.split('=')
		if info == "PROBLEM":
			title = line

pl.plot(solucoes_melhor, label='Melhor indivíduo',color='green')
pl.plot(solucoes_media, label='Média da população', color='gold')
pl.plot(solucoes_pior, label='Pior indivíduo', color='red')
pl.legend()
worse = 2
best = 0

for i in range(0, len(solucoes_melhor)):
	if solucoes_melhor[i] > best:
		best = solucoes_melhor[i]

for i in range(0, len(solucoes_pior)):
	if solucoes_pior[i] < worse:
		worse = solucoes_pior[i]

limit_worse = worse - 0.05
limit_best = best + 0.05
limit_x_low = -50
limit_x_high = 1050

solution = 'Melhor solução: '+ str(best)

pl.title(title+' -- '+ solution)
pl.xlabel('Gerações')
pl.ylabel('Fitness')
pl.ylim([limit_worse, limit_best])
pl.xlim([limit_x_low,limit_x_high])

pl.show()