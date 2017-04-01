/**
 * Copyright (c) 2014-2016 by the respective copyright holders.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 */
package org.openhab.binding.gumyns.internal;

import org.eclipse.smarthome.core.thing.Thing;
import org.eclipse.smarthome.core.thing.ThingTypeUID;
import org.eclipse.smarthome.core.thing.binding.BaseThingHandlerFactory;
import org.eclipse.smarthome.core.thing.binding.ThingHandler;
import org.openhab.binding.gumyns.Binding;
import org.openhab.binding.gumyns.handler.BridgeHandler;
import org.openhab.binding.gumyns.handler.GenericThingHandler;
import org.zeromq.ZContext;

/**
 * The {@link GumynsHandlerFactory} is responsible for creating things and thing
 * handlers.
 *
 * @author gumyns - Initial contribution
 */
public class GumynsHandlerFactory extends BaseThingHandlerFactory {

    private final ZContext context = new ZContext(4);

    @Override
    public boolean supportsThingType(ThingTypeUID thingTypeUID) {
        return thingTypeUID.getBindingId().equals(Binding.ID);
    }

    @Override
    protected ThingHandler createHandler(Thing thing) {
        return thing.getThingTypeUID().getId().equals(BridgeHandler.THING_TYPE.getId())
                ? new BridgeHandler(thing, context) : new GenericThingHandler(thing);
    }

    interface HandlerFactory {
        ThingHandler create(Thing thing);
    }
}
