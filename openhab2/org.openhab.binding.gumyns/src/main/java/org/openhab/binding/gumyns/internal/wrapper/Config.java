package org.openhab.binding.gumyns.internal.wrapper;

import java.util.stream.Collectors;

import org.eclipse.smarthome.core.thing.Thing;
import org.openhab.binding.gumyns.Binding;

public class Config {

    public static Binding binding(Thing thing) {
        String addr = (String) thing.getConfiguration().get("addr");
        return new Binding(getBinding(thing), addr);
    }

    private static String getBinding(Thing thing) {
        return thing.getUID().getAsString();// + getChannels(thing);
    }

    private static String getChannels(Thing thing) {
        return thing.getChannels().stream().map(channel -> channel.getChannelTypeUID().getAsString().split(":"))
                .map(array -> array[array.length - 1]).collect(Collectors.toList()).toString();
    }
}
