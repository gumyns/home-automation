package org.openhab.binding.gumyns.internal.wrapper;

import java.math.BigDecimal;

import org.eclipse.smarthome.core.thing.Bridge;

public final class BridgeConfig {

    private static final String connection_pattern = "tcp://%s:%d";

    private static final String property_ip = "ip", property_port = "port";

    public final String connection;

    public final String subscriber;

    private BridgeConfig(String ip, BigDecimal port) {
        this.connection = String.format(connection_pattern, ip == null ? "127.0.0.1" : ip,
                port.intValue() > 0 ? port.intValue() : 12542);
        this.subscriber = String.format(connection_pattern, ip == null ? "127.0.0.1" : ip,
                port.intValue() + 1 > 0 ? port.intValue() + 1 : 12543);
    }

    public static BridgeConfig from(Bridge bridge) {
        return new BridgeConfig((String) bridge.getConfiguration().get(property_ip),
                (BigDecimal) bridge.getConfiguration().get(property_port));
    }
}
