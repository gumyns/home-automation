package org.openhab.binding.gumyns.internal;

import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.Optional;

import org.eclipse.smarthome.core.thing.ThingTypeUID;
import org.eclipse.smarthome.core.thing.binding.ThingTypeProvider;
import org.eclipse.smarthome.core.thing.type.BridgeType;
import org.eclipse.smarthome.core.thing.type.ChannelDefinition;
import org.eclipse.smarthome.core.thing.type.ChannelTypeUID;
import org.eclipse.smarthome.core.thing.type.ThingType;
import org.openhab.binding.gumyns.Binding;
import org.openhab.binding.gumyns.internal.model.config.ThingJson;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.google.gson.Gson;

public class GumynsThingTypeProvider implements ThingTypeProvider {

    private final Logger logger = LoggerFactory.getLogger(GumynsThingTypeProvider.class);

    private Map<ThingTypeUID, ThingType> thingTypesByUID = new HashMap<ThingTypeUID, ThingType>();

    public GumynsThingTypeProvider() {
        ThingTypeUID thingType = new ThingTypeUID(Binding.ID, "bridge");
        thingTypesByUID.put(thingType, new BridgeType(thingType, null, "Gumyns server", null, null, null, null, null));
        List<String> bridges = Collections.singletonList(thingType.getAsString());
        try {
            FileReader reader = new FileReader("gumyns.things.json");
            Optional.ofNullable(new Gson().fromJson(reader, ThingJson[].class)).map(array -> {
                for (int i = 0; i < array.length; i++) {
                    ThingJson thing = array[i];
                    ThingTypeUID type = new ThingTypeUID(Binding.ID, thing.getId());
                    List<ChannelDefinition> channels = new ArrayList<>(thing.getChannels().length);
                    for (int j = 0; j < thing.getChannels().length; j++) {
                        channels.add(new ChannelDefinition(thing.getChannels()[j],
                                new ChannelTypeUID(Binding.ID, thing.getChannels()[j])));
                    }
                    thingTypesByUID.put(type,
                            new ThingType(type, bridges, thing.getName(), null, channels, null, null, null));

                }
                return null;
            });
            reader.close();
        } catch (IOException e) {
            logger.error("PLUGIN", e);
        }

    }

    @Override
    public Collection<ThingType> getThingTypes(Locale locale) {
        return thingTypesByUID.values();
    }

    @Override
    public ThingType getThingType(ThingTypeUID thingTypeUID, Locale locale) {
        return thingTypesByUID.get(thingTypeUID);
    }

}
