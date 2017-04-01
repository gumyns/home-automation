package org.openhab.binding.gumyns.internal;

import java.io.FileReader;
import java.io.IOException;
import java.util.Collection;
import java.util.HashMap;
import java.util.Locale;
import java.util.Map;
import java.util.Optional;

import org.eclipse.smarthome.core.thing.type.ChannelGroupType;
import org.eclipse.smarthome.core.thing.type.ChannelGroupTypeUID;
import org.eclipse.smarthome.core.thing.type.ChannelType;
import org.eclipse.smarthome.core.thing.type.ChannelTypeProvider;
import org.eclipse.smarthome.core.thing.type.ChannelTypeUID;
import org.openhab.binding.gumyns.Binding;
import org.openhab.binding.gumyns.internal.model.config.ChannelJson;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.google.gson.Gson;

public class GumynsChannelTypeProvider implements ChannelTypeProvider {

    private static final Logger logger = LoggerFactory.getLogger(GumynsChannelTypeProvider.class);

    private Map<ChannelTypeUID, ChannelType> channels = new HashMap<ChannelTypeUID, ChannelType>();
    private Map<ChannelGroupTypeUID, ChannelGroupType> channelGroups = new HashMap<ChannelGroupTypeUID, ChannelGroupType>();

    public GumynsChannelTypeProvider() {
        try {
            FileReader reader = new FileReader("gumyns.channels.json");
            Optional.ofNullable(new Gson().fromJson(reader, ChannelJson[].class)).map(array -> {
                for (int i = 0; i < array.length; i++) {
                    ChannelJson channel = array[i];
                    ChannelTypeUID uid = new ChannelTypeUID(Binding.ID, channel.getId());
                    channels.put(uid, new ChannelType(uid, false, channel.getType(), channel.getName(),
                            channel.getDescription(), null, null, null, null));

                }
                return null;
            });
            reader.close();
        } catch (IOException e) {
            logger.error("PLUGIN", e);
        }
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public Collection<ChannelType> getChannelTypes(Locale locale) {
        return channels.values();
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public ChannelType getChannelType(ChannelTypeUID channelTypeUID, Locale locale) {
        return channels.get(channelTypeUID);
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public ChannelGroupType getChannelGroupType(ChannelGroupTypeUID channelGroupTypeUID, Locale locale) {
        return channelGroups.get(channelGroupTypeUID);
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public Collection<ChannelGroupType> getChannelGroupTypes(Locale locale) {
        return channelGroups.values();
    }

}
