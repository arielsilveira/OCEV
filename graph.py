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


pl.plot(solucoes_melhor, color='green')
pl.plot(solucoes_media, color='gold')
pl.plot(solucoes_pior, color='red')

pl.title('NQueens ')
pl.xlabel('Gerações')
pl.ylabel('Fitness')
pl.ylim([0,1.05])
pl.xlim([0,1000])

pl.show()