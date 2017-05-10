import matplotlib as plt
import mpl_toolkits
mpl_toolkits.__path__.append('/usr/lib/python2.7/dist-packages/mpl_toolkits/')
from mpl_toolkits.basemap import Basemap

# create the map
map = Basemap(llcrnrlon=-119, llcrnrlat=22, urcrnrlon=-64, urcrnrlat=49,
              projection='lcc', lat_1=33, lat_2=45,lon_0=-95)

# load the shapefile
map.readshapefile('../output/st99_d00', name='states', drawbounds=True)

# draw the map
savefig('../output/foo.png')
