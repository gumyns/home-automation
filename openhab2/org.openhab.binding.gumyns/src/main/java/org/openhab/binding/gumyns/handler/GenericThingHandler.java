package org.openhab.binding.gumyns.handler;

import java.util.Optional;

import org.eclipse.smarthome.core.thing.ChannelUID;
import org.eclipse.smarthome.core.thing.Thing;
import org.eclipse.smarthome.core.thing.ThingStatus;
import org.eclipse.smarthome.core.thing.ThingStatusDetail;
import org.eclipse.smarthome.core.thing.ThingStatusInfo;
import org.eclipse.smarthome.core.thing.binding.BaseThingHandler;
import org.eclipse.smarthome.core.types.Command;
import org.eclipse.smarthome.core.types.RefreshType;
import org.openhab.binding.gumyns.Binding;
import org.openhab.binding.gumyns.internal.model.message.BindingMessage;
import org.openhab.binding.gumyns.internal.model.message.Message;
import org.openhab.binding.gumyns.internal.model.message.RefreshMessage;
import org.openhab.binding.gumyns.internal.model.message.WriteMessage;
import org.openhab.binding.gumyns.internal.wrapper.Config;
import org.openhab.binding.gumyns.internal.wrapper.JsonHelper;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.zeromq.ZContext;
import org.zeromq.ZMQ;
import org.zeromq.ZMQ.Socket;

import com.google.gson.JsonElement;

public class GenericThingHandler extends BaseThingHandler {

    private final Logger logger = LoggerFactory.getLogger(GenericThingHandler.class);

    public GenericThingHandler(Thing thing) {
        super(thing);
    }

    @Override
    public void bridgeStatusChanged(ThingStatusInfo bridgeStatusInfo) {
        bridgeStatusChanged(bridgeStatusInfo, getThing().getStatusInfo());
    }

    @Override
    public void updateStatus(ThingStatus status) {
        updateStatus(status, ThingStatusDetail.NONE, null);
    }

    protected Binding binding() {
        return Config.binding(thing);
    }

    protected ZContext context() {
        return ((BridgeHandler) getBridge().getHandler()).context();
    }

    public String connection() {
        return ((BridgeHandler) getBridge().getHandler()).connection();
    }

    public void bridgeStatusChanged(ThingStatusInfo bridgeStatus, ThingStatusInfo thingStatus) {
        // if (bridgeStatus.getStatus() == ThingStatus.ONLINE
        // && thingStatus.getStatusDetail() == ThingStatusDetail.BRIDGE_OFFLINE) {
        // switchRpc = SwitchPrxHelper.checkedCast(proxy(Switch.ice_staticId));
        // updateStatus(switchRpc.status(Config.from(thing)) ? ThingStatus.ONLINE : ThingStatus.OFFLINE);
        // } else if (bridgeStatus.getStatus() == ThingStatus.OFFLINE) {
        // switchRpc = null;
        // updateStatus(ThingStatus.OFFLINE, ThingStatusDetail.BRIDGE_OFFLINE);
        // }
    };

    public void updateState(ChannelUID channelUID, JsonElement value) {
        Optional.ofNullable(thing.getChannel(channelUID.getId())).ifPresent(
                channel -> updateState(channelUID, JsonHelper.fromJson(channel.getAcceptedItemType(), value)));
    }

    @Override
    public void handleCommand(ChannelUID channelUID, Command command) {
        logger.debug("COMMAND -> {} {}", channelUID.getIdWithoutGroup(), command.getClass().getSimpleName());
        Message message = null;
        if (command instanceof RefreshType) {
            message = RefreshMessage.create(binding());
        } else {
            message = Optional.ofNullable(JsonHelper.toJson(channelUID.getIdWithoutGroup(), command))
                    .map(array -> WriteMessage.create(binding(), array)).orElse(RefreshMessage.create(binding()));
        }
        if (message != null) {
            Socket socket = context().createSocket(ZMQ.REQ);
            socket.connect(connection());
            socket.send(message.serialize());
        }
    }

    @Override
    public void initialize() {
        if (getBridge().getStatus() == ThingStatus.ONLINE) {
            Socket socket = context().createSocket(ZMQ.REQ);
            socket.connect(connection());
            socket.send(BindingMessage.create(binding()).serialize());
        }
    }

}