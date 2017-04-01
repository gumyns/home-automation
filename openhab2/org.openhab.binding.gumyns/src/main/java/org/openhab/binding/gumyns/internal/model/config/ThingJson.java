package org.openhab.binding.gumyns.internal.model.config;

public class ThingJson {

    String id, name;

    String[] channels;

    ThingJson() {

    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String[] getChannels() {
        return channels;
    }
}
