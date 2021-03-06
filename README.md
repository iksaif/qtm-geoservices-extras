# Qt Mobility Geoservices Extras

This package contains additional geoservices for Qt Mobility providing integration
with OpenStreetMap and Google Maps.

## Example

    QMap<QString, QVariant> parameters;

    parameters["mapping.servers"] = (
      QStringList("http://a.tile.opencyclemap.org/cycle/")
        << "http://b.tile.opencyclemap.org/cycle/"
	<< "http://c.tile.opencyclemap.org/cycle/");

    if (serviceProvider)
        delete serviceProvider;

    serviceProvider = new QGeoServiceProvider("openstreetmap", parameters);

    if (serviceProvider->error() != QGeoServiceProvider::NoError) {
        QMessageBox::information(
	    this, tr("Error"),
            tr("Unable to find the %1 geoservices plugin.").arg(providerId));
	qApp->quit();
	return;
    }

    mapManager = serviceProvider->mappingManager();


## OpenStreetMap (openstreetmap)

### API
OpenStreetMap creates and provides free geographic data such as street maps to anyone who wants them.
The project was started because most maps you think of as free actually have legal or technical
restrictions on their use, holding back people from using them in creative, productive, or unexpected ways.

* http://openstreetmap.org/
* http://wiki.openstreetmap.org/wiki/Tiles

### Parameters

    mapping.servers:
        type:           QString / QStringList
        default:        http://tile.openstreetmap.org/
        description:    openstreetmap tile server(s)
                        if a list is specified, the manager will used
                        round robin to balance request between servers.
                        The trailing slash is *needed*.
                        Examples:
                         Use two servers: ("http://a.tile.openstreetmap.org/",
                                           "http://b.tile.openstreetmap.org/")
                         OpenCycleMaps: ("http://tile.opencyclemap.org/cycle/")

    mapping.server:         alias for mapping.servers

    mapping.proxy:
        type:           QString
        default:        application global proxy settings
        description:    http proxy used for network queries [host[:port]].
                        default port is 8080.

    mapping.cache.directory:
        type:           QString
        default:        temporary directory
        description:    Cache directory.

    mapping.cache.size:
        type:           long long (or QString)
        default:        default QNetworkDiskCache cache size
        description:    cache size, may be limited by the platform.


## Google

### API

To use this plugin you must read and accept Google's Terms of Use available
at: http://code.google.com/apis/maps/terms.html

http://code.google.com/apis/maps/documentation/

Tiles from:
* http://mt.google.com/vt/lyrs=h@137&x=%1&y=%2&z=%3 (streets)
* http://mt.google.com/vt/lyrs=&x=%1&s=&y=%2&z=%3 (streets + terrain)
* http://khm.google.com/kh?v=51&x=%1&s=&y=%2&z=%3 (sat)

### Parameters


    mapping.proxy:
        type:           QString
        default:        application global proxy settings
        description:    http proxy used for network queries [host[:port]].
                        default port is 8080.

    mapping.cache.directory:
        type:           QString
        default:        temporary directory
        description:    Cache directory.

    mapping.cache.size:
        type:           long long (or QString)
        default:        default QNetworkDiskCache cache size
        description:    cache size, may be limited by the platform.


## Google - Static Map (experimental/google EXPERIMENTAL)

This is an attempt to use static Map API, but it does not work well
right now.

### API

The Google Static Map service creates your map based on URL parameters
sent through a standard HTTP request and returns the map as an image you
can display on your web page.

http://code.google.com/apis/maps/documentation/staticmaps/

### Parameters

    mapping.proxy:
        type:           QString
        default:        application global proxy settings
        description:    http proxy used for network queries [host[:port]].
                        default port is 8080.

    mapping.cache.directory:
        type:           QString
        default:        temporary directory
        description:    Cache directory.

    mapping.cache.size:
        type:           long long (or QString)
        default:        default QNetworkDiskCache cache size
        description:    cache size, may be limited by the platform.

    mapping.sensor:
        type:           bool
        default:        false
        description:    specifies whether the application requesting the static
                        map is using a sensor to determine the user's location.

    mapping.tilesize:
        type:           QSize
        default:        QSize(256, 256)
        description:    size of the files, size can be as big as
                        640x640. Tweak the size according to the size
                        of your screen and your network configuration.
                        256x256 is the recommended size.

    mapping.format:
        type:           QString [png8, png32, gif, jpeg jpeg-baseline]
        default:        none (server default: png32)
        description:    choose the format of the tiles
                        - png8 or png (default) specifies the 8-bit PNG format.
                        - png32 specifies the 32-bit PNG format.
                        - gif specifies the GIF format.
                        - jpg specifies the JPEG compression format.
                        - jpg-baseline specifies a non-progressive JPEG compression format.

    mapping.language:
        type:           QString
        default:        none
        description:    defines the language to use for display of labels on map tiles.
                        Note that this parameter is only supported for some country tiles;
                        if the specific language requested is not supported for the tile set,
                        then the default language for that tileset will be used.
                        Examples: fr-FR, en-US, ...
