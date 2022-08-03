FROM ubuntu:focal

LABEL maintainer "ali.cicerali@orioninc.com"

#=============
# Set WORKDIR
#=============
WORKDIR /root

#=============
# Set Timezone
#=============
ENV TZ=Europe/Istanbul
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
#

#==================
# General Packages
#------------------
# supervisor
#   Process manager
#------------------
#  NoVNC Packages
#------------------
# x11vnc
#   VNC server for X display
#       We use package from ubuntu 18.10 to fix crashing issue
# openbox
#   Windows manager
# python-xdg
#   Required by openbox autostart function
# python-numpy
#   Numpy, For faster performance: https://github.com/novnc/websockify/issues/77
# net-tools
#   Netstat
#==================
ADD x11vnc.pref /etc/apt/preferences.d/
RUN apt-get -qqy update && apt-get -qqy install --no-install-recommends \
    supervisor \
    x11vnc \
    openbox \
    net-tools \
    xvfb \
    python-xdg \
    python-numpy \
    unzip \
    wget \
 && apt clean all \
 && rm -rf /var/lib/apt/lists/*
    
#=======
# noVNC
# Use same commit id that docker-selenium uses
# https://github.com/elgalu/docker-selenium/blob/236b861177bd2917d864e52291114b1f5e4540d7/Dockerfile#L412-L413
#=======
ENV NOVNC_SHA="b403cb92fb8de82d04f305b4f14fa978003890d7" \
    WEBSOCKIFY_SHA="558a6439f14b0d85a31145541745e25c255d576b"
RUN  wget --no-check-certificate -nv -O noVNC.zip "https://github.com/kanaka/noVNC/archive/${NOVNC_SHA}.zip" \
 && unzip -x noVNC.zip \
 && rm noVNC.zip  \
 && mv noVNC-${NOVNC_SHA} noVNC \
 && wget --no-check-certificate -nv -O websockify.zip "https://github.com/kanaka/websockify/archive/${WEBSOCKIFY_SHA}.zip" \
 && unzip -x websockify.zip \
 && mv websockify-${WEBSOCKIFY_SHA} ./noVNC/utils/websockify \
 && rm websockify.zip \
 && ln noVNC/vnc_auto.html noVNC/index.html

#================================================ 
# noVNC Default Configurations
# These Configurations can be changed through -e
#================================================
ARG APP_RELEASE_VERSION=1.5-p0
ENV DISPLAY=:0 \
    SCREEN=0 \
    SCREEN_WIDTH=672 \
    SCREEN_HEIGHT=552 \
    SCREEN_DEPTH=16 \
    LOCAL_PORT=5900 \
    TARGET_PORT=6080 \
    TIMEOUT=1 \
    VIDEO_PATH=/tmp/video \
    LOG_PATH=/var/log/supervisor \
    GA=true \
    GA_ENDPOINT=https://www.google-analytics.com/collect \
    GA_TRACKING_ID=UA-133466903-1 \
    GA_API_VERSION="1" \
    APP_RELEASE_VERSION=$APP_RELEASE_VERSION \
    APP_TYPE=Device

#================================================
# openbox configuration
# Update the openbox configuration files to:
#   + Use a single virtual desktop to prevent accidentally switching 
#   + Add background
#================================================
ADD rc.xml /etc/xdg/openbox/rc.xml

#===============
# Expose Ports
#---------------
# 6080
#   noVNC port
#===============
EXPOSE 6080

#===================
# Run docker-appium
#===================
#COPY src /root/src
COPY vnc.sh tetris.sh tetris libSDL2* /root/
COPY supervisord.conf /root/
RUN ln -s /usr/bin/python3 /usr/bin/python && \
    chmod +x /root/vnc.sh /root/tetris /root/tetris.sh && \
    chmod +x /root/supervisord.conf

CMD /usr/bin/supervisord --configuration supervisord.conf
