## clear existing workspace
rm(list = ls())

## load required packages
if(!require(maps)){install.packages('maps'); library(maps)}

## load data set 
nn = read.csv('../output/nn.csv')
ddmst = read.csv('../output/dmst.csv')
christo = read.csv('../output/christo.csv')

## Plot the maps
pdf(file = '../output/nnplot.pdf', width = 6.5, height = 5)
map('state')
points(nn[,4], nn[,3], col ='red', pch = 19, cex = 0.30)
for(ii in 1:1000)
{
  lines(x = c(nn[ii,4], nn[ii+1,4]), y = c(nn[ii,3], nn[ii+1,3]), lwd = 1, col = 'blue')
}
dev.off()

pdf(file = '../output/dmstplot.pdf', width = 6.5, height = 5)
map('state')
points(ddmst[,4], ddmst[,3], col ='red', pch = 19, cex = 0.30)
for(ii in 1:1000)
{
  lines(x = c(ddmst[ii,4], ddmst[ii+1,4]), y = c(ddmst[ii,3], ddmst[ii+1,3]), lwd = 1, col = 'blue')
}
dev.off()

pdf(file = '../output/christoplot.pdf', width = 6.5, height = 5)
map('state')
points(christo[,4], christo[,3], col ='red', pch = 19, cex = 0.30)
for(ii in 1:1000)
{
  lines(x = c(christo[ii,4], christo[ii+1,4]), y = c(christo[ii,3], christo[ii+1,3]), lwd = 1, col = 'blue')
}
dev.off()

