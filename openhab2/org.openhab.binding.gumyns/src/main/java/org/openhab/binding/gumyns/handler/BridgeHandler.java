package org.openhab.binding.gumyns.handler;

import java.util.Map.Entry;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;

import org.eclipse.smarthome.core.thing.Bridge;
import org.eclipse.smarthome.core.thing.ChannelUID;
import org.eclipse.smarthome.core.thing.Thing;
import org.eclipse.smarthome.core.thing.ThingStatus;
import org.eclipse.smarthome.core.thing.ThingTypeUID;
import org.eclipse.smarthome.core.thing.ThingUID;
import org.eclipse.smarthome.core.thing.binding.BaseBridgeHandler;
import org.eclipse.smarthome.core.types.Command;
import org.openhab.binding.gumyns.Binding;
import org.openhab.binding.gumyns.internal.model.frame.IdentFrame;
import org.openhab.binding.gumyns.internal.model.message.Message;
import org.openhab.binding.gumyns.internal.model.message.MessageType;
import org.openhab.binding.gumyns.internal.wrapper.BridgeConfig;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.zeromq.ZContext;
import org.zeromq.ZMQ;
import org.zeromq.ZMQ.Socket;

import com.google.gson.Gson;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;

public class BridgeHandler extends BaseBridgeHandler {

    public final static ThingTypeUID THING_TYPE = new ThingTypeUID(Binding.ID, "bridge");

    private final Gson gson = new Gson();

    private final Logger logger = LoggerFactory.getLogger(BridgeHandler.class);

    private String connection;

    private final ZContext context;

    private final ScheduledExecutorService scheduler = Executors.newScheduledThreadPool(3);

    public BridgeHandler(Thing bridge, ZContext context) {
        super((Bridge) bridge);
        this.context = context;
        scheduler.execute(() -> {
            Socket subscriber = context().createSocket(ZMQ.SUB);
            subscriber.connect(BridgeConfig.from(getThing()).subscriber);
            subscriber.subscribe(new byte[] { (byte) MessageType.IDENT.value });
            while (true) {
                try {
                    Message message = Message.deserialize(subscriber.recv());
                    logger.debug("IDENT <-- {}", message);
                    GenericThingHandler handler = (GenericThingHandler) getThingByUID(
                            new ThingUID(IdentFrame.from(gson, message).binding())).getHandler();
                    handler.updateStatus(ThingStatus.ONLINE);
                    logger.debug("IDENT {} {} ", handler.getThing().getStatus(), message);
                } catch (Exception e) {
                    logger.error("IDENT thread fail", e);
                    try {
                        Thread.sleep(5000);
                    } catch (InterruptedException e1) {
                    }
                }
            }
        });
        scheduler.execute(() -> {
            Socket subscriber = context().createSocket(ZMQ.SUB);
            subscriber.connect(BridgeConfig.from(getThing()).subscriber);
            subscriber.subscribe(new byte[] { (byte) MessageType.JSON.value });
            while (true) {
                Message message = Message.deserialize(subscriber.recv());
                JsonObject json = gson.fromJson(new String(message.data).trim(), JsonObject.class);

                logger.debug("JSON <-- {}", message);
                for (JsonElement element : json.get("r").getAsJsonArray()) {
                    for (Entry<String, JsonElement> entry : element.getAsJsonObject().entrySet()) {
                        ChannelUID channel = new ChannelUID(json.get("b").getAsString() + ":" + entry.getKey());
                        GenericThingHandler handler = (GenericThingHandler) getThingByUID(
                                new ThingUID(IdentFrame.from(gson, message).binding())).getHandler();
                        handler.updateState(channel, entry.getValue());
                    }
                }
            }
        });
    }

    public ZContext context() {
        return context;
    }

    public String connection() {
        return connection;
    }

    @Override
    public void handleCommand(ChannelUID channelUID, Command command) {
        // if (command instanceof ThingDisconnectedCommand) {
        // if (getThing().getStatus() != ThingStatus.OFFLINE) {
        // updateStatus(ThingStatus.OFFLINE, ThingStatusDetail.COMMUNICATION_ERROR);
        // }
        // context.destroy();
        // tryToConnect(BridgeConfig.from(getThing()));
        // }
    }

    @Override
    public void initialize() {
        // scheduler.scheduleAtFixedRate(() -> {
        //
        // }, 0, 5, TimeUnit.SECONDS);
        tryToConnect(BridgeConfig.from(getThing()));
    }

    @Override
    public void dispose() {
        if (getThing().getStatus() != ThingStatus.OFFLINE) {
            updateStatus(ThingStatus.OFFLINE);
        }
        context.destroy();
        super.dispose();
    }

    private void tryToConnect(BridgeConfig config) {
        this.connection = config.connection;
        logger.debug("IDENT Bridge: {}", String.valueOf(connection));
        scheduler.execute(() -> {
            logger.debug("IDENT Bridge 0: {}", String.valueOf(connection));
            while (getThing().getStatus() != ThingStatus.ONLINE) {
                logger.debug("IDENT Bridge 1: {}", String.valueOf(connection));
                Socket socket = context.createSocket(ZMQ.REQ);
                logger.debug("IDENT Bridge 2: {}", String.valueOf(connection));
                socket.connect(config.connection);
                logger.debug("IDENT Bridge 3: {}", String.valueOf(connection));
                socket.send(new Message(MessageType.ACK).serialize());
                logger.debug("I <-- {}", Message.deserialize(socket.recv()));
                if (getThing().getStatus() != ThingStatus.ONLINE) {
                    updateStatus(ThingStatus.ONLINE);
                    logger.debug("IDENT Bridge 4: {}", String.valueOf(connection));
                }
            }
        });
    }
}
